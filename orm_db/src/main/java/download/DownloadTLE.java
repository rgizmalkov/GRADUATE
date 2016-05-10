package download; /**
 * Created by Рома on 11.07.2015.
 */

import javax.net.ssl.HttpsURLConnection;
import java.io.*;
import java.net.CookieHandler;
import java.net.CookieManager;
import java.net.CookiePolicy;
import java.net.URL;
import java.nio.file.Paths;
import java.util.Scanner;

public class DownloadTLE {

    /**
     * @param "args"
     */
    public DownloadTLE(){
    }


    public static synchronized void download() {
        try {
            String baseURL = "https://www.space-track.org";
            String authPath = "/auth/login";
            String userName = "dangerilo@gmail.com";
            String password = "flenka_spectr_rungekutta";
            String query = "https://www.space-track.org/basicspacedata/query/class/tle_latest/ORDINAL/1/EPOCH/%3Enow-30/orderby/NORAD_CAT_ID/format/tle";

            CookieManager manager = new CookieManager();
            manager.setCookiePolicy(CookiePolicy.ACCEPT_ALL);
            CookieHandler.setDefault(manager);

            URL url = new URL(baseURL+authPath);

            HttpsURLConnection conn = (HttpsURLConnection) url.openConnection();
            conn.setDoOutput(true);
            conn.setRequestMethod("GET");

            String input = "identity="+userName+"&password="+password;

            OutputStream os = conn.getOutputStream();
            os.write(input.getBytes());
            os.flush();

            BufferedReader br = null;
            BufferedWriter bw = null;
            File file = new File("src/main/resources/files/full_catalog.txt");
            try {
                br = new BufferedReader(new InputStreamReader((conn.getInputStream())));
                bw = new BufferedWriter(new FileWriter(file));

                String output;
                System.out.println("Output from Server .... \n");

                url = new URL(query);

                br = new BufferedReader(new InputStreamReader((url.openStream())));

                while ((output = br.readLine()) != null) {
                    bw.write(output+'\n');
                }


                url = new URL(baseURL + "/ajaxauth/logout");
                br = new BufferedReader(new InputStreamReader((url.openStream())));
                conn.disconnect();
            }catch (IOException ex){
                    System.out.println("Class: DownloadTLE; Method: DownloadTLE; Interrupted Exception");
                    ex.printStackTrace();
            }
            finally {
                try {
                    bw.flush();
                    bw.close();
                    br.close();
                }catch (IOException exe){
                    System.out.println("FLUSH/CLOSE EXCEPTION");
                    exe.printStackTrace();
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}