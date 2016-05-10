package consturctor;

import orm.Satellite;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by Рома on 09.05.2016.
 */
public class ConstructEntities {
    public static ArrayList<Satellite> method(File file) {
        ArrayList<Satellite> sats = new ArrayList<>();
        try (Scanner sc = new Scanner(file)) {
            while (sc.hasNextLine()) {
                String line1 = sc.nextLine();
                String line2 = sc.nextLine();
                sats.add(Satellite.newInstance(line1, line2));
            }
        } catch (FileNotFoundException ex) {
            System.out.println("Class: ConstructEntities; Method: method; FNF");
            ex.printStackTrace();
        }
        return sats;
    }
    public ArrayList<Satellite> method1(File file) {
        ArrayList<Satellite> sats = new ArrayList<>();
        try (Scanner sc = new Scanner(file)) {
            while (sc.hasNextLine()) {
                String line1 = sc.nextLine();
                String line2 = sc.nextLine();
                sats.add(new Satellite(line1, line2));
            }
        } catch (FileNotFoundException ex) {
            System.out.println("Class: ConstructEntities; Method: method; FNF");
            ex.printStackTrace();
        }
        return sats;
    }
    public static int[] julDateToDateTime(double JD) {
        int Year, Month, Day, Hour, Min;
        double Sec;
        if (JD <= 0) {
            Year = 0;
            Month = 0;
            Day = 0;
            Hour = 0;
            Min = 0;
            Sec = 0;
        } else {
            long a, b, c, d, e, f;
            double FracOfDay;
            //Преобразуем номер юлианского дня в календарную дату
            a = (long) (JD + 0.5);
            if (a < 2299161) {
                b = 0;
                c = a + 1524;
            } else {
                b = (long) ((a - 1867216.25) / 36524.25);
                c = a + b - (b / 4) + 1525;
            }
            d = (long) ((c - 122.1) / 365.25);
            e = 365 * d + d / 4;
            f = (long) ((c - e) / 30.6001);
            Day = (int) (c - e - (int) (30.6001 * f));
            Month = (int) (f - 1 - 12 * (f / 14))-1;
            Year = (int) (d - 4715 - ((7 + Month) / 10));
            FracOfDay = (JD - 0.5 - (int) (JD - 0.5)) * 24.0;//вещественное количество часов
            Hour = (int) (FracOfDay);                  //целое количество часов
            FracOfDay = (FracOfDay - Hour) * 60.0;      //вещественное количество минут
            Min = (int) (FracOfDay);                  //целое количество минут
            Sec = (FracOfDay - Min) * 60.0;              //вещественное количество секунд
        }
        return new int[]{Year, Month, Day, Hour, Min, (int)Sec};
    }
}
