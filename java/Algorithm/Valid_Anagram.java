package Algorithm;

import java.util.HashMap;
import java.util.Map;

/**
 * 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的一个字母异位词。
 *
 * 示例 1:
 *
 * 输入: s = "anagram", t = "nagaram"
 * 输出: true
 * 示例 2:
 *
 * 输入: s = "rat", t = "car"
 * 输出: false
 * 说明:
 * 你可以假设字符串只包含小写字母。
 *
 * 进阶:
 * 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
 * */
public class Valid_Anagram {
    /**
     * 方法1. 排序 然后比较排序好的字符串 O(nlog(n))
     * 方法2. 使用Map计数　O(N)
     * */
    public boolean isAnagram(String s, String t) {
        Map<Character,Integer> maps = new HashMap<Character, Integer>();
        Map<Character,Integer> mapt = new HashMap<Character, Integer>();
        if(s.length() != t.length()) return false;
        for (int i = 0; i < s.length(); i++) {
            Character sc = s.charAt(i);
            Character tc = t.charAt(i);
            if(maps.containsKey(sc)) maps.put(sc,maps.get(sc)+1);
            else maps.put(sc,1);
            if(mapt.containsKey(tc)) mapt.put(tc,mapt.get(tc)+1);
            else mapt.put(tc,1);
        }
        return maps.equals(mapt);
    }
}
