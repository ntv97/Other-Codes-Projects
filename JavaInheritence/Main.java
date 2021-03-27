package Dogs;

public class Main {
    public static void main(String[] args) {
        Dogs Biscuit = new Dogs("Biscuit", 'M', "Yorkiepoo", "Farn & White", "Small");
        Dogs Gwen = new Dogs("Gwen", 'F', "Beagles", "Black, White & Tan", "Small");
        Dogs Wolcott = new Dogs("Wolcott", 'M', "Cocker Spaniel", "Buff" ,"Medium");
        Dogs Penny = new Dogs("Penny", 'F', "Jack Russell Terrier", "Tri-Colored", "Small");
        Dogs Lane = new Dogs("Lane", 'M', "Dalmatian", "White & Black", "Medium");

        Biscuit.get_info();
        Yorkiepoo biscuit = new Yorkiepoo("Cream", 'M', "Brown", "Small");
        biscuit.message();
        System.out.print("\n");
        Gwen.get_info();
        Beagles gwen = new Beagles("Vanilla", 'F', "Creamy White", "Small");
        gwen.message();
        System.out.print("\n");
        Wolcott.get_info();
        Crocker walcott = new Crocker("Walcott", 'M', "Walnut", "Medium");
        walcott.message();
        System.out.print("\n");
        Penny.get_info();
        Jack penny = new Jack("Penny", 'F', "Bronze", "Small");
        penny.message();
        System.out.print("\n");
        Lane.get_info();
        Dalmatian lane = new Dalmatian("Lane", 'M', "Creamy White", "Medium");
        lane.message();


    }
}
