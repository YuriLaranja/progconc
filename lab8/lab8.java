
class BufferLimitado {
   static final int N = 5;
   private double[] buffer = new double[N];
   private int count = 0;

   BufferLimitado() {
      System.out.println("Printando Buffer:");
      for (int i = 0; i < N; i++) {
         buffer[i] = 0;
         System.out.print(" " + buffer[i]);
      }

      System.out.println(" ");
   }

   private void imprimeBuffer() {
      for (int i = 0; i < N; i++) {
         System.out.print(" " + buffer[i]);
      }
      System.out.println("");
   }

   public synchronized void insere(int id) {
      try {
         System.out.println("Produtor " + id + " chegou para inserir");
         while (count == N) {
            System.out.println("Produtor " + id + " bloqueado");
            this.wait();
            System.out.println("Produtor " + id + " liberado");
         }
         for (int i = 0; i < N; i++) {
            if (buffer[i] == 0) {
               buffer[i] = 1;
               count++;
               break;
            }
         }
         System.out.println("Produtor " + id + " inseriu");
         imprimeBuffer();
         notifyAll();
      } catch (InterruptedException e) {
      }
   }

   public synchronized void retira(int id) {
      try {
         System.out.println("Consumidor " + id + " chegou para consumir");
         while (count == 0) {
            System.out.println("Consumidor " + id + " sem elemento para consumir");
            this.wait();
            System.out.println("Consumidor " + id + " liberado");
         }
         for (int i = 0; i < N; i++) {
            if (buffer[i] == 1) {
               count--;
               buffer[i] = 0;
               break;
            }
         }
         System.out.println("Consumidor " + id + " retirou");
         imprimeBuffer();
         notifyAll();
      } catch (InterruptedException e) {
         return;
      }
   }

}

class Consumidor extends Thread {
   int id;
   BufferLimitado buffer;

   Consumidor(int id, BufferLimitado buffer) {
      this.id = id;
      this.buffer = buffer;
   }

   public void run() {
      int k = 0;
      while (k < 11) {
         this.buffer.retira(this.id);
         for (int i = 0; i < 1000000000; i++) {
            int j = 10; // loop bobo
            j += 10;
         }
         k++;
      }

   }
}

class Produtor extends Thread {
   int id;
   BufferLimitado buffer;

   Produtor(int id, BufferLimitado buffer) {
      this.id = id;
      this.buffer = buffer;
   }

   public void run() {
      int k = 0;
      while (k < 11) {
         this.buffer.insere(this.id);
         for (int i = 0; i < 1000000000; i++) {
            int j = 0; // loop bobo
            j += 10;
         }
         k++;
      }

   }
}

class ProdCons {
   static final int Cons = 1; //NUMERO DE CONSUMIDORES
   static final int Prod = 4; //NUMERO DE PRODUTORES

   public static void main(String[] args) {
      int i;
      BufferLimitado buffer = new BufferLimitado();
      Consumidor[] consumidor = new Consumidor[Cons];
      Produtor[] produtor = new Produtor[Prod];

      for (i = 0; i < Prod; i++) {
         produtor[i] = new Produtor(i + 1, buffer);
         produtor[i].start();
      }
      for (i = 0; i < Cons; i++) {
         consumidor[i] = new Consumidor(i + 1, buffer);
         consumidor[i].start();
      }
   }
}