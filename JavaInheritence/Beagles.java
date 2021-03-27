package Dogs;

public class Beagles extends Dogs {
    public Beagles(String n, char g, String c, String s) {
        super(n, g, "Gwen", c, s);
    }

    @Override
    public void message() {
        System.out.println("Hi! I'm Gwen under type Beagles.");
    }
}
