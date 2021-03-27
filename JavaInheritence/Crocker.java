package Dogs;

public class Crocker extends Dogs {
    public Crocker(String n, char g, String c, String s) {
        super(n, g, "Crocker Spaniel", c, s);
    }

    @Override
    public void message() {
        System.out.println("Hi, I'm a Walcott type Crocker Spaniel");
    }
}
