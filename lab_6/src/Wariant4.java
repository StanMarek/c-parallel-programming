public class Wariant4 extends Thread{

    private Obraz obraz;
    private int id;
    private  char c;

    Wariant4(Obraz image, char c, int id){
        this.obraz = image;
        this.c = c;
        this.id = id;
    }
    Wariant4(Obraz image, int c, int id) {
        this(image, (char) c, id);
    }

    public void start() {
        int ilosc = obraz.return_number(this.c);
        String info = "Numer watku:" + this.id + " " + this.c;
        obraz.pokaz_ilosc(info, ilosc);
    }
}
