import java.util.Scanner;
import java.math.BigInteger;


public class Main {



    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);

        BigInteger a = input.nextBigInteger();
        BigInteger b = input.nextBigInteger();
        a = a.subtract(BigInteger.valueOf(1));

        BigInteger res = f(b).subtract(f(a));

        System.out.println(res.toString());
    }

    public static BigInteger f(BigInteger x)
    {
        BigInteger l, r, mid;

        l = BigInteger.ZERO;
        r = BigInteger.TEN;
        r = r.pow(50);

        while(!l.equals(r))
        {
            mid = l.add(r).add(BigInteger.ONE).divide(BigInteger.valueOf(2));

            if(check(mid, x))
                l = mid;
            else
                r = mid.subtract(BigInteger.ONE);
        }

        return l;
    }

    public static boolean check(BigInteger mid, BigInteger x)
    {
        if(mid.multiply(mid.add(BigInteger.ONE)).compareTo(x) <= 0)
            return true;

        return false;
    }

}
