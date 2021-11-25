import java.util.Scanner;

class Histogram_test {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);

        obraz_1.calculate_histogram();
        obraz_1.print_histogram();

        System.out.println("Liczba watkow: ");
        int num_threads = scanner.nextInt();
        System.out.println("--- 3 ---");
        Thread[] lista_watkow = new Thread[num_threads];
        for (int i = 0; i < num_threads; i++) {
            Thread watek = new Watek(i, obraz_1, num_threads);
            lista_watkow[i] = watek;
            watek.start();
        }
        for (int i = 0; i < num_threads; i++){
            try {
                lista_watkow[i].join();
            } catch (InterruptedException e) {e.printStackTrace();}
        }
        obraz_1.compare_histograms();
        obraz_1.clear_histogram_parallel();

        System.out.println("--- 4 ---");
        Thread[] lista_watkow_4 = new Thread[num_threads];
        for (int i = 0; i < num_threads; i++) {
            Thread watek = new Wariant4(obraz_1, i+33, i);
            lista_watkow_4[i] = watek;
            watek.start();
        }
        for (int i = 0; i < num_threads; i++){
            try {
                lista_watkow_4[i].join();
            } catch (InterruptedException e) {e.printStackTrace();}
        }

        System.out.println("--- 5 ---");
        Wariant5[] lista_watkow_5 = new Wariant5[num_threads];
        int skok = 94 / num_threads;
        int loss = 94 - skok * num_threads;
        for (int i = 0; i < num_threads; i++) {
            if(i != num_threads - 1) {
                int start = skok * i + 33;
                int end = skok * (i + 1) + 32;
                Wariant5 watek = new Wariant5(obraz_1, i, start, end);
                lista_watkow_5[i] = watek;
                watek.run(); }
            else {
                int start = skok * i + 33;
                int end = skok * (i + 1) + 32 + loss;
                Wariant5 watek = new Wariant5(obraz_1, i, start, end);
                lista_watkow_5[i] = watek;
                watek.run();
            }
        }
//        for (int i = 0; i < num_threads; i++){
//            try {
//                lista_watkow_5[i].();
//            } catch (InterruptedException e) {e.printStackTrace();}
//        }

    }

}
