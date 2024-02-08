package river_monitoring_service;

public enum F {
    F1(3000),
    F2(1000);

    private final int value;

    F(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
