package Dogs;
public class Dalmatian extends Dogs {
    public Dalmatian(String n, char g, String c, String s) {
        super(n, g, "Dalmatian", c, s);
    }
    @Override
    public void message() {
        System.out.println("Hi! I am a Dalmatian named Lane.");
    }
}
