package orm;

import javax.persistence.*;

/**
 * Created by Рома on 09.05.2016.
 */
@Entity
@Table(name = "TLE")
@Access(AccessType.FIELD)
public class TLE {
    @Id
    private int id;
    /* first line */
    @Column(nullable = false, length = 15)
    private  String _numberOfLine1;
    @Column(nullable = false, length = 15)
    private  String _satelliteNumbers1;//NORAD

    @Column(nullable = false, length = 15)
    private  String _classification;
    @Column(nullable = false, length = 15)
    private  String _internationalDesignatorYear;
    @Column(nullable = false, length = 15)
    private  String _internationalDesignator;
    @Column(nullable = false, length = 15)
    private  String _piece;
    @Column(nullable = false, length = 15)
    private  String _epochYear;
    @Column(nullable = false, length = 15)
    private  String _epochTime;
    @Column(nullable = false, length = 15)
    private  String _meanMotionDerivative;
    @Column(nullable = false, length = 15)
    private  String _meanMotionSecondDerivative;
    @Column(nullable = false, length = 15)
    private  String  _averageAcceleration;
    @Column(nullable = false, length = 15)
    private  String _typeOfEphemeris;
    @Column(nullable = false, length = 15)
    private  String _elementsNumber;
    @Column(nullable = false, length = 15)
    private  String _chkSum;

    /* second line */
    @Column(nullable = false, length = 15)
    private  String _numberOfLine2;
    @Column(nullable = false, length = 15)
    private  String _satelliteNumbers2;
    @Column(nullable = false, length = 15)
    private  String _inclination;
    @Column(nullable = false, length = 15)
    private  String _rightAscensionOfTheNode;
    @Column(nullable = false, length = 15)
    private  String _eccentricity;
    @Column(nullable = false, length = 15)
    private  String _argOfPerigee;
    @Column(nullable = false, length = 15)
    private  String _meanAnomaly;
    @Column(nullable = false, length = 15)
    private  String _meanMotion;
    @Column(nullable = false, length = 15)
    private  String epochRev;
    @Column(nullable = false, length = 15)
    private  String _chk;

    public TLE(){}

    public TLE(String line1, String line2){
        this._numberOfLine1 = line1.substring(0,1);
        this._satelliteNumbers1 = line1.substring(2,7);
        this._classification = line1.substring(7,8);
        this._internationalDesignatorYear = line1.substring(9,11);
        this._internationalDesignator = line1.substring(11,14);
        this._piece = line1.substring(14,17);
        this._epochYear = line1.substring(18,20);
        this._epochTime = line1.substring(20,32);
        this._meanMotionDerivative = line1.substring(33,43);
        this._meanMotionSecondDerivative = line1.substring(44,52);
        this._averageAcceleration = line1.substring(53,61);
        this._typeOfEphemeris = line1.substring(62,63);
        this._elementsNumber = line1.substring(64, 68);
        this._chkSum = String.valueOf(line1.charAt(68));

        this._numberOfLine2 = line2.substring(0, 1);
        this._satelliteNumbers2 = line2.substring(2,7);
        this._inclination = line2.substring(8,16);
        this._rightAscensionOfTheNode = line2.substring(17,25);
        this._eccentricity = line2.substring(26,33);
        this._argOfPerigee = line2.substring(34,42);
        this._meanAnomaly = line2.substring(43,51);
        this._meanMotion = line2.substring(52,63);
        this.epochRev = line2.substring(63, 68);
        this._chk = String.valueOf(line2.charAt(68));
        this.id= Integer.valueOf(this.get_satelliteNumbers1().replaceAll(" ", ""));;

    }

    public int getId() {
        return id;
    }

    public String get_numberOfLine1() {
        return _numberOfLine1;
    }

    public String get_satelliteNumbers1() {
        return _satelliteNumbers1;
    }

    public String get_classification() {
        return _classification;
    }

    public String get_internationalDesignatorYear() {
        return _internationalDesignatorYear;
    }

    public String get_internationalDesignator() {
        return _internationalDesignator;
    }

    public String get_piece() {
        return _piece;
    }

    public String get_epochYear() {
        return _epochYear;
    }

    public String get_epochTime() {
        return _epochTime;
    }

    public String get_meanMotionDerivative() {
        return _meanMotionDerivative;
    }

    public String get_meanMotionSecondDerivative() {
        return _meanMotionSecondDerivative;
    }

    public String get_averageAcceleration() {
        return _averageAcceleration;
    }

    public String get_typeOfEphemeris() {
        return _typeOfEphemeris;
    }

    public String get_elementsNumber() {
        return _elementsNumber;
    }

    public String get_chkSum() {
        return _chkSum;
    }

    public String get_numberOfLine2() {
        return _numberOfLine2;
    }

    public String get_satelliteNumbers2() {
        return _satelliteNumbers2;
    }

    public String get_inclination() {
        return _inclination;
    }

    public String get_rightAscensionOfTheNode() {
        return _rightAscensionOfTheNode;
    }

    public String get_eccentricity() {
        return _eccentricity;
    }

    public String get_argOfPerigee() {
        return _argOfPerigee;
    }

    public String get_meanAnomaly() {
        return _meanAnomaly;
    }

    public String get_meanMotion() {
        return _meanMotion;
    }

    public String getEpochRev() {
        return epochRev;
    }

    public String get_chk() {
        return _chk;
    }

    @Override
    public String toString() {
        return "TLE{" +
                "id=" + id +
                ", _numberOfLine1='" + _numberOfLine1 + '\'' +
                ", _satelliteNumbers1='" + _satelliteNumbers1 + '\'' +
                ", _classification='" + _classification + '\'' +
                ", _internationalDesignatorYear='" + _internationalDesignatorYear + '\'' +
                ", _internationalDesignator='" + _internationalDesignator + '\'' +
                ", _piece='" + _piece + '\'' +
                ", _epochYear='" + _epochYear + '\'' +
                ", _epochTime='" + _epochTime + '\'' +
                ", _meanMotionDerivative='" + _meanMotionDerivative + '\'' +
                ", _meanMotionSecondDerivative='" + _meanMotionSecondDerivative + '\'' +
                ", _averageAcceleration='" + _averageAcceleration + '\'' +
                ", _typeOfEphemeris='" + _typeOfEphemeris + '\'' +
                ", _elementsNumber='" + _elementsNumber + '\'' +
                ", _chkSum='" + _chkSum + '\'' +
                ", _numberOfLine2='" + _numberOfLine2 + '\'' +
                ", _satelliteNumbers2='" + _satelliteNumbers2 + '\'' +
                ", _inclination='" + _inclination + '\'' +
                ", _rightAscensionOfTheNode='" + _rightAscensionOfTheNode + '\'' +
                ", _eccentricity='" + _eccentricity + '\'' +
                ", _argOfPerigee='" + _argOfPerigee + '\'' +
                ", _meanAnomaly='" + _meanAnomaly + '\'' +
                ", _meanMotion='" + _meanMotion + '\'' +
                ", epochRev='" + epochRev + '\'' +
                ", _chk='" + _chk + '\'' +
                '}';
    }
}
