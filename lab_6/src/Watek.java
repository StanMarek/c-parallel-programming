public class Watek extends Thread{

    private int id;
    private Obraz obraz;
    private int nThreads;

    public Watek(int id, Obraz obraz, int n) {
        this.id = id;
        this.obraz = obraz;
        this.nThreads = n;
    }

    public void start() {
        obraz.calculate_histogram_parallel_thread(id, nThreads);
        obraz.print_histogram_parallel(id, nThreads);
    }

}
