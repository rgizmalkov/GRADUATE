package main;

import consturctor.ConstructEntities;
import download.DownloadTLE;
import orm.Satellite;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.io.File;
import java.util.ArrayList;

/**
 * Created by Рома on 09.05.2016.
 */
public class Main {
    public static void main(String[] args) {
        File file = new File("src/main/resources/files/full_catalog.txt");
        if (!(file.exists() && file.isFile())) DownloadTLE.download();
        ArrayList<Satellite> sats = ConstructEntities.method(file);
//        for(Satellite sat : sats)
//            System.out.println(sat);


        EntityManagerFactory emf = Persistence.createEntityManagerFactory("satellites");
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx;
        for(Satellite sat : sats){
            System.out.println(sat);
            tx = em.getTransaction();
            tx.begin();
            em.persist(sat.getTle());
            em.persist(sat.getKep());
            em.persist(sat.getState());
            em.persist(sat);
            tx.commit();
        }

        em.close();
        emf.close();
    }
}
