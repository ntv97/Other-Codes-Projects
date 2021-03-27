package Dogs;
public class Jack extends Dogs {
    Jack(String n, char g, String c, String s) {
        super(n, g, "Jack Russell Terrier", c, s);
    }
    @Override
    public void message() {
        System.out.println("Hi! I'm Penny and I'm a Jack Russell Terrier");
    }
}
