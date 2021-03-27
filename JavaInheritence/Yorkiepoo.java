package Dogs;

public class Yorkiepoo extends Dogs {

    public Yorkiepoo(String n, char g, String c, String s) {
        super(n, g, "Yorkiepoo", c, s);
    }

    @Override
    public void message() {
        System.out.println("I am type Yorkiepoo named Biscuit!");
    }
}
