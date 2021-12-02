import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

public class Simple_executor_test {

    public static void main(String[] args) {

		System.out.println("Stanislaw Marek\n");

//		Counter counter = new Counter();
//		ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
//
//		for (int i = 0; i < 50; i++) {
//			Runnable worker = new CounterPlus(counter);
//			executor.execute(worker);
//		}
//
//		// This will make the executor accept no new threads
//		// and finish all existing threads in the queue
//		executor.shutdown();
//
//		// Wait until all threads finish
//		while (!executor.isTerminated()) {}
//
//		System.out.println("Finished all threads");
//		System.out.format("\nCounter_1: %d, Counter_2 %d\n\n",
//				  counter.get_c1(), counter.get_c2());

//		double a = 0;
//		double b = Math.PI;
//		double dx = (b - a)/1000000;
//		Calka_callable c = new Calka_callable(a, b, dx);
//		double wynik = 0;
//		try {
//			wynik = c.compute();
//		} catch (Exception e) {
//			e.printStackTrace();
//		}
//		System.out.println("Calka sekwencyjnie = " + wynik);

//		final int N_THREADS = 8;
//		ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(N_THREADS);
//		List<Future<Double>> list = new ArrayList<>();
//		double a = 0;
//		double b = Math.PI;
//		double N = 80; // liczba rdzeni x 10
//		double dx = (b-a)/N;
//		double result = 0;
//		for (int i = 0; i < N; i++) {
//			Callable<Double> callable = new Calka_callable(
//					a + i * dx,
//					a + (i + 1) * dx,
//					dx
//			);
//			Future<Double> future = executor.submit(callable);
//			list.add(future);
//		}
//		for(Future<Double> future : list) {
//			try {
//				result += future.get();
//			}
//			catch (Exception e) {
//				e.printStackTrace();
//			}
//		}
//		System.out.println("\nSuma calki = " + result);
//		executor.shutdown();

		int SIZE = 15;
		int[] tablica = new int[SIZE];
		for(int i = 0; i < SIZE; i++)
			tablica[i] = ThreadLocalRandom.current().nextInt(0, 100 + 1);
		System.out.println("Przed:" + Arrays.toString(tablica));

		DivideTask task = new DivideTask(tablica);
		ForkJoinPool forkJoinPool = new ForkJoinPool();
		forkJoinPool.execute(task);

		System.out.println("Po: " + Arrays.toString(task.join()));
	}

} 
