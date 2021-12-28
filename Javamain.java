class Javamain{
	static {
        System.loadLibrary("test");
    }
    public native String test(String n);
    
      public static void main(String[] args) {
      		Javamain java = new Javamain();
      		String out = java.test("010A");
      		 System.out.println(out);  
      }

}
