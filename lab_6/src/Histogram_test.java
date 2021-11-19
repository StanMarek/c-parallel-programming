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

        System.out.println("Set number of threads");
        int num_threads = scanner.nextInt();
        Watek[] NewThr = new Watek[num_threads];
        for (int i = 0; i < num_threads; i++) {
            int id = i;
            (NewThr[i] = new Watek(id ,obraz_1, num_threads)).run();
        }
        for (int i = 0; i < num_threads; i++) {
            try {
                NewThr[i].join();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        obraz_1.compare_histograms();
        obraz_1.clear_histogram_parallel();

        Wariant4Thread[] wariant4 = new Wariant4Thread[94];
        for (int i = 0; i < wariant4.length; i++) {
            (wariant4[i] = new Wariant4Thread(i,i+33, obraz_1)).run();
        }
        for (int i = 0; i < wariant4.length; i++) {
            try {
                wariant4[i].join();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }
}
