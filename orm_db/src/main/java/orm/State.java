package orm;

import javax.persistence.*;

/**
 * Created by Рома on 09.05.2016.
 */
@Entity
@Table(name = "STATE")
@Access(AccessType.FIELD)
public class State {
    @Id
    private int id;
    @Column(nullable = false, length = 25)
    private double rx;
    @Column(nullable = false, length = 25)
    private double ry;
    @Column(nullable = false, length = 25)
    private double rz;
    @Column(nullable = false, length = 25)
    private double vx;
    @Column(nullable = false, length = 25)
    private double vy;
    @Column(nullable = false, length = 25)
    private double vz;

    public State(){}

    public State(int id, double rx, double ry, double rz, double vx, double vy, double vz) {
        this.id = id;
        this.rx = rx;
        this.ry = ry;
        this.rz = rz;
        this.vx = vx;
        this.vy = vy;
        this.vz = vz;
    }

    @Override
    public String toString() {
        return "State{" +
                "id=" + id +
                ", rx=" + rx +
                ", ry=" + ry +
                ", rz=" + rz +
                ", vx=" + vx +
                ", vy=" + vy +
                ", vz=" + vz +
                '}';
    }
}
