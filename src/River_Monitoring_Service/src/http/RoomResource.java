package RoomService.http;

import RoomService.RoomState;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.CorsHandler;

/**
 * Class for the http service, it contains the handlers for the room resource:
 * get handler for the movement (esp) and light (arduino) histories;
 * post handler to send a new command to Arduino.
 * */
public class RoomResource extends AbstractVerticle {

	private final int port;

	public RoomResource(final int port) {
		this.port = port;
	}

	@Override
	public void start() {
		Router router = Router.router(vertx);
		router.route().handler(CorsHandler.create("http://localhost"));
		router.get("/api/room").handler(this::handleGetResource);
		router.post("/api/room").handler(this::handlePostResource);
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}

	/**
	 * Get handler for the movement and light histories.
	 * */
	private void handleGetResource(final RoutingContext routingContext) {
		JsonObject res = new JsonObject();
		res.put("light", RoomState.getInstance().getLightStateHistory().stream()
		        .map(msg -> new ResponseData(msg.getMsgDate(), msg.getDay()))
		        .toList());
		res.put("movement", RoomState.getInstance().getMovementStateHistory().stream()
		        .map(msg -> new ResponseData(msg.getDateTime(), msg.getMovementState()))
		        .toList());

		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(res.encodePrettily());
	}

	/**
	 * Post handler to send a new command to Arduino.
	 * */
	private void handlePostResource(final RoutingContext routingContext) {
	    routingContext.request().bodyHandler(bodyHandler -> {
	        var body = bodyHandler.toJsonObject();
	        RoomState.getInstance().addDashboardMessage(new DashboardMessage(Boolean.parseBoolean(body.getString("light")),
	                    Integer.parseInt(body.getString("movement"))));
	    });
	    routingContext.response()
    	        .putHeader("content-type", "application/json")
                .end(new JsonObject().encodePrettily());
	}

	private void log(final String msg) {
		System.out.println("[ROOM RESOURCE] " + msg);
	}

	/**
	 * Class to pack the data to be sent to the client.
	 * */
	private final class ResponseData {

            private String date;
            private boolean value;

	    public ResponseData(final String date, final boolean value) {
	        this.date = date;
	        this.value = value;
	    }

	    @SuppressWarnings("unused")
            public String getDate() {
	    	return this.date;
	    }

	    @SuppressWarnings("unused")
            public boolean isValue() {
	    	return this.value;
	    }

            @SuppressWarnings("unused")
            public void setDate(final String date) {
                this.date = date;
            }

            @SuppressWarnings("unused")
            public void setValue(final boolean value) {
                this.value = value;
            }
	}

}