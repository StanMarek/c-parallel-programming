import  java.util.Random;


class Obraz {

    private int size_n;
    private int size_m;
    private char[][] tab;
    private char[] tab_symb;
    private int[] histogram;

    private Object lock_histogram = new Object();
    private int[] hist_parallel;

    public Obraz(int n, int m) {

        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];
        tab_symb = new char[94];

        final Random random = new Random();

        // for general case where symbols could be not just integers
        for(int k=0;k<94;k++) {
            tab_symb[k] = (char)(k+33); // substitute symbols
        }

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                tab[i][j] = tab_symb[random.nextInt(94)];  // ascii 33-127
                //tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
                System.out.print(tab[i][j]+" ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        histogram = new int[94];
        hist_parallel = new int[94];
        clear_histogram();
        clear_histogram_parallel();
    }

    public void clear_histogram(){
        for(int i=0;i<94;i++) histogram[i]=0;
    }

    public void clear_histogram_parallel(){
        for(int i=0;i<94;i++) hist_parallel[i]=0;
    }

    public void calculate_histogram(){
        for(int i=0;i<size_n;i++) {
            for(int j=0;j<size_m;j++) {
                // optymalna wersja obliczania histogramu, wykorzystujaca fakt, źe symbole w tablicy
                // mozna przeksztalcic w indeksy tablicy histogramu
                // histogram[(int)tab[i][j]-33]++;

                // wersja bardziej ogolna dla tablicy symboli nie utozsamianych z indeksami
                // tylko dla tej wersji sensowne jest zrownoleglenie w dziedzinie zbioru znakow ASCII
                for(int k=0;k<94;k++) {
                    if(tab[i][j] == tab_symb[k]) histogram[k]++;
                    //if(tab[i][j] == (char)(k+33)) histogram[k]++;
                }
            }
        }
    }

    public void calculate_histogram_parallel(int nThreads){
        Thread[] threads = new Thread[nThreads];
        for (int i = 0; i < nThreads; i++) {
            threads[i] = new Thread();
            calculate_histogram_parallel_thread(threads[i], i, nThreads);
        }

        for (int i = 0; i < nThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }
    public void increment_histogram_char(int index) {
        synchronized(lock_histogram) {
            this.hist_parallel[index]++;
        }
    }

    public void calculate_histogram_parallel_thread(Thread thread, int threadId, int nThreads) {
        thread.start();
        int start = threadId;
        int end = this.size_n;
        int stride = nThreads;


        for(int i = start; i < end; i+=stride) {
            for(int j = 0; j < this.size_m; j++) {
                for(int k=0;k<94;k++) {
                    if(tab[i][j] == tab_symb[k]) {
                        increment_histogram_char(k);
                    }
                }
            }
        }
    }

    public void print_histogram(){
        for(int i=0;i<94;i++) {
            System.out.print(tab_symb[i]+" "+histogram[i]+"\n");
            //System.out.print((char)(i+33)+" "+histogram[i]+"\n");
        }
    }

    public void print_histogram_parallel(){
        for(int i=0;i<94;i++) {
            System.out.print(tab_symb[i]+" "+hist_parallel[i]+"\n");
            //System.out.print((char)(i+33)+" "+histogram[i]+"\n");
        }
    }

    public void compare_histograms() {
        int error = 0;
        for(int i = 0; i < 94; i++) {
            if(histogram[i] != hist_parallel[i]) {
                error += histogram[i] - hist_parallel[i];
                System.out.println("Blad symbol: " + tab_symb[i] + " histogram:" + histogram[i] + " histogram_par:" + hist_parallel[i]);
            }
        }
        System.out.println("Histogramy porownane, liczba bledow: " + error + " blad: " + (double)(100 * error/(size_m * size_n)) + "%");
    }
}