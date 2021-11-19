public class Wariant4Thread extends Thread{

    private int id;
    private int obserwuj;
    private char obserwujChar;
    private Obraz obraz;

    public Wariant4Thread(int id, int obserwuj, Obraz obraz) {
        this.id = id;
        this.obserwuj = obserwuj;
        this.obraz = obraz;
        this.obserwujChar = (char) obserwuj;
        System.out.println("obserwuje char: " + this.obserwujChar);
    }

    public void run() {
        obraz.calculate_histogram_parallel_w4(obserwuj);
        obraz.print_histogram_parallel_w4(id, obserwuj);
    }
}
