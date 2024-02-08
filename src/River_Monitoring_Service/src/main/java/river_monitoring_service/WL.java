package river_monitoring_service;

public enum WL {
    WL1(15),
    WL2(12),
    WL3(8),
    WL4(4);

    private final int value;

    WL(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
