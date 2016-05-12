package orm;

import consturctor.ConstructEntities;
import nativepack.NativeClass;

import javax.persistence.*;
import java.util.Date;
import java.util.GregorianCalendar;

/**
 * Created by Рома on 09.05.2016.
 */
@Entity
@Table(name = "SAT")
@Access(AccessType.FIELD)
public class Satellite {
    @Id
    private int id;
    @Temporal(TemporalType.TIMESTAMP) @Column (nullable = false)
    private Date realDate;
    @Temporal(TemporalType.TIMESTAMP) @Column (nullable = false)
    private Date exchangedDate;
    @Column(length = 50, nullable = true)
    private String typeOfSatellite;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "kep")
    private KeplerianElements kep;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "tle")
    private TLE tle;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "state")
    private State state;

    public Satellite(){}

    public Satellite (String line1, String line2){
        this.tle = new TLE(line1, line2); // Tow-line elements

        int num = this.tle.getId();
        double[] kep = NativeClass.jepoch(line1, line2);

        this.state = new State(num,kep[0],kep[1],kep[2],kep[3],kep[4],kep[5], kep[6]); //State: Vectors V and R

        double[] kep_in = {kep[0],kep[1],kep[2],kep[3],kep[4],kep[5]};
        double[] kepel = NativeClass.coordsToElements(kep_in);

        this.kep = new KeplerianElements(num,kepel[0],kepel[1],kepel[2],kepel[3],kepel[4],kepel[5]); // Keplerian elements

        this.id = num;
        System.out.println(kep[6]);
        int[] gc_vars = ConstructEntities.julDateToDateTime(kep[6]);
        GregorianCalendar gc = new GregorianCalendar(gc_vars[0],gc_vars[1],gc_vars[2],gc_vars[3],gc_vars[4],gc_vars[5]);
        this.realDate = gc.getTime();
        this.exchangedDate = this.realDate;

    }

    public static Satellite newInstance(String line1, String line2){
        Satellite sat = new Satellite();
        sat.tle = new TLE(line1, line2); // Tow-line elements

        int num = sat.tle.getId();
        double[] kep = NativeClass.jepoch(line1, line2);

        sat.state = new State(num,kep[0],kep[1],kep[2],kep[3],kep[4],kep[5], kep[6]); //State: Vectors V and R

        double[] kep_in = {kep[0],kep[1],kep[2],kep[3],kep[4],kep[5]};
        double[] kepel = NativeClass.coordsToElements(kep_in);

        sat.kep = new KeplerianElements(num,kepel[0],kepel[1],kepel[2],kepel[3],kepel[4],kepel[5]); // Keplerian elements

        sat.id = num;
        int[] gc_vars = ConstructEntities.julDateToDateTime(kep[6]);
        System.out.println(kep[6]);
        GregorianCalendar gc = new GregorianCalendar(gc_vars[0],gc_vars[1],gc_vars[2],gc_vars[3],gc_vars[4],gc_vars[5]);
        sat.realDate = gc.getTime();
        sat.exchangedDate = sat.realDate;
        return sat;
    }

    public int getId() {
        return id;
    }

    public Date getRealDate() {
        return realDate;
    }

    public Date getExchangedDate() {
        return exchangedDate;
    }

    public String getTypeOfSatellite() {
        return typeOfSatellite;
    }

    public KeplerianElements getKep() {
        return kep;
    }

    public TLE getTle() {
        return tle;
    }

    public State getState() {
        return state;
    }

    @Override
    public String toString() {
        return "Satellite{" +
                "id=" + id +
                ", realDate=" + realDate +
                ", exchangedDate=" + exchangedDate +
                ", typeOfSatellite='" + typeOfSatellite + '\'' +
                ", kep=" + kep +
                ", tle=" + tle +
                ", state=" + state +
                '}';
    }


}
