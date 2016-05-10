package orm;

import javax.persistence.*;

/**
 * Created by Рома on 09.05.2016.
 */
@Entity
@Table(name = "KEP")
@Access(AccessType.FIELD)
public class KeplerianElements {
    @Id
    private int id;
    @Column(nullable = false, length = 25)
    private double a;
    @Column(nullable = false, length = 25)
    private double e;
    @Column(nullable = false, length = 25)
    private double i;
    @Column(nullable = false, length = 25)
    private double q;
    @Column(nullable = false, length = 25)
    private double w;
    @Column(nullable = false, length = 25)
    private double o;

    public KeplerianElements(){}

    public KeplerianElements(int id, double a, double e, double i, double q, double w, double o) {
        this.id = id;
        this.a = a;
        this.e = e;
        this.i = i;
        this.q = q;
        this.w = w;
        this.o = o;
    }

    @Override
    public String toString() {
        return "KeplerianElements{" +
                "id=" + id +
                ", a=" + a +
                ", e=" + e +
                ", i=" + i +
                ", q=" + q +
                ", w=" + w +
                ", o=" + o +
                '}';
    }
}
