package river_monitoring_service.http;

import river_monitoring_service.RiverMonitoringSystemState;
import river_monitoring_service.RunService;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

/**
 * Class for the http service, it contains the handlers for the river resource:
 * get handler for the waterlevel (esp) histories;
 * post handler to send a new command to Arduino.
 * */
public class RiverResource extends AbstractVerticle {

	private final int port;

	public RiverResource(final int port) {
		this.port = port;
	}

	@Override
	public void start() {
		Router router = Router.router(vertx);
		router.route().handler(CorsHandler.create("http://localhost"));
		router.route().handler(BodyHandler.create());
		router.get("/api/river").handler(this::handleGetResource);
		router.post("/api/river").handler(this::handlePostResource);
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}

	/**
	 * Get handler for the state of Arduino (state and automatic), waterlevel (esp) histories and dashboard messages.
	 * */
	private void handleGetResource(final RoutingContext routingContext) {
		JsonObject res = new JsonObject();
		res.put("state", RunService.getCurrentState());
		res.put("waterLevel", RiverMonitoringSystemState.getInstance().getLastWaterLevel().get().getWaterLevel());
		res.put("dashboard", RunService.getDashboard());
		res.put("automatic", RunService.getAutomatic());

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
			int valveOpening = Integer.parseInt(body.getString("valveOpening"));
		
			RiverMonitoringSystemState.getInstance().addDashboardMessage(new DashboardMessage(valveOpening));

			// Invia una risposta al client (se necessario)
			routingContext.response()
				.putHeader("content-type", "application/json")
				.end(new JsonObject().encodePrettily());
			});
	}

	private void log(final String msg) {
		System.out.println("[RIVER RESOURCE] " + msg);
	}
}