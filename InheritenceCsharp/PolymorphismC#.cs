using System;

namespace MilkPolymorphism
{
    class Program
    {
        static void Main(string[] args)
        {
            Milk regular = new Milk(8, 149);
            SoyMilk soy = new SoyMilk(4, 131, 10);
            AlmondMilk almond = new AlmondMilk(3, 30, "Silk");

            soy.ChangeFlavor();
            almond.ChangeFlavor();

            regular.PrintNutrition();
            soy.PrintNutrition();
            almond.PrintNutrition();
        }
    }

    class Milk
    {
        protected int Fat;
        protected int Calories;
        protected string Flavor;

        public Milk ()
        {
            Console.WriteLine("One milk object created!\n");
        }

        public Milk(int fat, int calories)
        {
            Fat = fat;
            Calories = calories;
        }

        virtual public void ChangeFlavor()
        {
            Flavor = "Chocolate";
        }

        virtual public void PrintNutrition()
        {
            Console.WriteLine($"Chocolate milk has {Fat}g of fat, and {Calories} calories per cup. ");
        } 

    }

    class SoyMilk : Milk
    {
        private int Sugar;

        public SoyMilk()
        {
            Console.WriteLine("One soy milk object created!\n");
        }

        public SoyMilk(int fat, int calories, int sugar) :
            base(fat, calories)
        {
            Sugar = sugar;
        }

        public override void ChangeFlavor()
        {
            Flavor = "vanilla";
        }

        public override void PrintNutrition()
        {
            Console.WriteLine($"Soy milk, {Flavor} flavor, has {Fat}g of fat, {Calories} calories per cup, and {Sugar} of " +
                $"sugar per cup.");
        }
    }

    class AlmondMilk : Milk
    {
        private string Brand;

        public AlmondMilk()
        {
            Console.WriteLine("One almond milk object created!");
        }

        public AlmondMilk(int fat, int calories, string brand) :
            base(fat, calories)
        {
            Brand = brand;
        }

        public override void ChangeFlavor()
        {
            Flavor = "original";
        }

        public override void PrintNutrition()
        {
            Console.Write($"{Brand}'s {Flavor} almond milk has {Fat}g of fat, and {Calories} calories per cup.");
        }
    }
}
    