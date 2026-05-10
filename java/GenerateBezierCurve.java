
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;

public class GenerateBezierCurve {

    // gets a point in a bezier line
    public static double[] getCubicBezierPoint(Point2D p0, Point2D p1, Point2D p2, Point2D p3, double t) {
        // bernstein polynomial for n = 3 : ((1 - t) ^ 3 * p0) + (3 * (1 - t) ^ 2 * t * p1) + (3 * (1 - t) * t ^ 2 * p2) + (t ^ 3 * p3)
        double u = 1 - t; // complement
        double x = u * u * u * p0.getX() + 3 * u * u * t * p1.getX() + 3 * u * t * t * p2.getX() + t * t * t * p3.getX();
        double y = u * u * u * p0.getY() + 3 * u * u * t * p1.getY() + 3 * u * t * t * p2.getY() + t * t * t * p3.getY();
        return new double[]{x, y};
    }

    // points to form a bezier line
    public static Object[] generateBezierCurve(Point2D p0, Point2D p1, Point2D p2, Point2D p3, Point2D center, double increment, String color) {
        int numBezierPoints = (int) Math.round(1.0 / increment);
        Object[] res = new Object[(numBezierPoints + 1) * 6];
        // center point
        res[0] = center.getX();
        res[1] = center.getY();
        res[2] = 0;
        res[3] = color;
        res[4] = center.getX();
        res[5] = center.getY();
        int idx = 6;
        for (double t = increment; t <= 1.00; t += increment) {
            double[] bezierPoint = getCubicBezierPoint(p0, p1, p2, p3, t);
            res[idx] = bezierPoint[0];
            res[idx + 1] = bezierPoint[1];
            res[idx + 2] = 0;
            res[idx + 3] = color;
            res[idx + 4] = bezierPoint[0];
            res[idx + 5] = bezierPoint[1];
            idx += 6;
        }
        return res;
    }

    public static void copyTextToClipboard(String text) {
        StringSelection stringSelection = new StringSelection(text);
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents(stringSelection, null);
    }

    public static void main(String[] args) {
        Point2D p0 = new Point2D(0.25, 0.27); // start
        Point2D p1 = new Point2D(0.24, 0.05); // control point 1
        Point2D p2 = new Point2D(0.245, 0.2); // control point 2
        Point2D p3 = new Point2D(0.4, 0.5); // end
        Point2D center = new Point2D(0, 0);
        double incSegments = 0.1;
        String color = "YELLOW";

        Object[] res = generateBezierCurve(p0, p1, p2, p3, center, incSegments, color);
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < res.length; i += 6) {
            sb.append(res[i]).append("f, ")
                    .append(res[i + 1]).append("f, ")
                    .append(res[i + 2]).append("f, ")
                    .append(res[i + 3]).append(", ")
                    .append(res[i + 4]).append("f, ")
                    .append(res[i + 5]).append("f,").append("\n");
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
