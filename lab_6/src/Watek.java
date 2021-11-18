public class Watek extends Thread{

    private int obserwuj;
    private char obserwujChar;
    private Obraz obraz;

    public Watek(int obserwuj, Obraz obraz) {
        this.obserwuj = obserwuj;
        this.obraz = obraz;
        this.obserwujChar = (char) obserwuj;
        System.out.println("obserwuje char: " + this.obserwujChar);
    }
}
