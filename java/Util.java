public class Util {

    public static int[] getRandom(int num) {
        int[] ints = new int[num];
        for (int i = 0; i < num; i++) {
            ints[i] = (int)(100*Math.random());
        }
        return ints;
    }

}
