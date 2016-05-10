package main;

import nativepack.NativeClass;
import orm.Satellite;

import java.util.Arrays;
import java.util.Properties;

/**
 * Created by Рома on 09.05.2016.
 */
public class Test {
    public static void main(String[] args) {
        String lane1 = "1 00050U 60009B   16129.07678851 -.00000087  00000-0 -14685-4 0  9996";
        String lane2 = "2 00050  47.2299 100.9837 0113174 171.5510 188.7216 12.20095477487363";
        Satellite sat = Satellite.newInstance(lane1, lane2);
        
        System.out.println(sat.getRealDate());
    }
}
