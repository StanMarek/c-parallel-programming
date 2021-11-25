public class Wariant5 implements Runnable{

    private Obraz obraz;
    private int id;
    private int start;
    private int end;

    Wariant5(Obraz image, int id, int start, int end){
        this.obraz = image;
        this.id = id;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        String info;
        for(int i = this.start; i <= this.end; i++)
        {
            info = "Numer watku:" + this.id + " " + (char)i;
            int ilosc_znakow = obraz.return_number((char)i);
            obraz.pokaz_ilosc(info, ilosc_znakow);
        }
    }
}
