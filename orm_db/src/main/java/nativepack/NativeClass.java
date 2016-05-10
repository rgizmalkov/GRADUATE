package nativepack;

/**
 * Created by Рома on 17.07.2015.
 */
public class NativeClass {
    static {
        try {
            System.loadLibrary("space_lib");
            System.out.println("Loaded");
        }catch (UnsatisfiedLinkError e) {
            //nothing to do
            System.out.println("Couldn't load Api");
            System.out.println(e.getMessage());
        }
    }
    native public static double[] jepoch(String lane1, String lane2);
    native public static double[] coordsToElements(double[] X);
}
