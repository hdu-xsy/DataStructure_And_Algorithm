package Algorithm;


import java.util.Stack;

/**
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 *
 * 有效字符串需满足：
 *
 * 左括号必须用相同类型的右括号闭合。
 * 左括号必须以正确的顺序闭合。
 * 注意空字符串可被认为是有效字符串。
 *
 * 示例 1:
 *
 * 输入: "()"
 * 输出: true
 * */

public class Valid_Parentheses {

    public boolean isValid(String s) {
        /**
         * 使用栈
         * */
        Stack<Character> stack = new Stack<Character>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if(c == '[' || c == '{' || c == '(') stack.push(c);
            if(c == ']') if(stack.empty() || stack.pop() != '[') return false;
            if(c == '}') if(stack.empty() || stack.pop() != '{') return false;
            if(c == ')') if(stack.empty() || stack.pop() != '(') return false;
        }
        if(!stack.empty()) return false;
        else return true;
    }
}
