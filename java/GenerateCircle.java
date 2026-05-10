
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;

class GenerateCircle {

    final static double PI = 3.14159265359;

    public static double[] generateCircleVertex(double x, double y, double red, double green, double blue, double radiusX, double radiusY, int triangleAmount) {
        double[] res = new double[triangleAmount * 18];
        double angleInc = (2 * PI) / triangleAmount; // 360 / amount of triangles
        double curAngle = 0;
        double aheadAngle = angleInc; // for left vertex
        int vertexCounter = 0; // for tracking which vertex
        for (int i = 0; i < res.length; i += 6) {
            int triangleSide = vertexCounter % 3; // to see which vertex we are at
            if (triangleSide == 0) { // center vertex
                res[i] = x;
                res[i + 1] = y;
            } else if (triangleSide == 1) { // right vertex
                res[i] = x + Math.cos(curAngle) * radiusX;
                res[i + 1] = y + Math.sin(curAngle) * radiusY;
            } else { // left vertex
                res[i] = x + Math.cos(aheadAngle) * radiusX;
                res[i + 1] = y + Math.sin(aheadAngle) * radiusY;
            }
            res[i + 2] = 0; // z
            res[i + 3] = red; // r
            res[i + 4] = green; // g
            res[i + 5] = blue; // b
            if (triangleSide == 0 && i != 0) { // checker so that it doesn't increment at left and right vertex everytime. (i != 0 since we start at degree = 0)
                curAngle += angleInc;
                aheadAngle += angleInc;
            }
            vertexCounter++;
        }
        return res;
    }

    // FROM: https://www.baeldung.com/java-clipboard-copy-paste-text
    public static void copyTextToClipboard(String text) {
        StringSelection stringSelection = new StringSelection(text);
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents(stringSelection, null);
    }

    public static void main(String[] args) {
        double x = -0.2655;
        double y = 0.50;
        double red = 0;
        double green = 0.29;
        double blue = 0.678;
        double radiusX = 0.13419917968;
        double radiusY = 0.13419917968;
        int triangleAmount = 30;
        double[] vertices = generateCircleVertex(x, y, red, green, blue, radiusX, radiusY, triangleAmount);
        // print
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < vertices.length; i += 6) {
            sb.append(vertices[i]).append("f, ")
                    .append(vertices[i + 1]).append("f, ")
                    .append(vertices[i + 2]).append("f, ")
                    .append(vertices[i + 3]).append("f, ")
                    .append(vertices[i + 4]).append("f, ")
                    .append(vertices[i + 5]).append("f,");
            if (i + 6 < vertices.length - 1) {
                sb.append("\n");
            }
        }
        String content = sb.toString();
        try {
            copyTextToClipboard(content);
            System.out.println("Copied: " + content);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
