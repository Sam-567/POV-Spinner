import java.awt.image.BufferedImage;

public class GridToArc {
	
	static final int SIZE = 400;
	static final int MODSTEPS = 10;
	static final int MODSTEPDISTANCE = SIZE / MODSTEPS;
	
	static final int ARGSTEPS = 20;
	static final int ANGLE = 400;
	//static final double 
	
	public static void main( String[] args) {
		
	}
	
	public void squareToRadial(BufferedImage image) {
		int xCenter = SIZE/2;
		int yCenter = SIZE/2;
		
		int[][][] radialImage = new int[3][36][10];
		//Too far out (x*x + y*y) >= (RadiusIn*RadiusIn);
		//To close (x*x + y*y) <= (RadiusOut*RadiusOut)
		
	}
	
	public void drawRadial() {
		
	}
	
	//10 MODs (10 led on one side)
	//20 Rads (positions of 10*)
	public void nextPos(int x, int y, int Arg, int Mod) {
		//Mod starts at 1 cause i want it to
		int OuterLimit = MODSTEPDISTANCE * Mod;
		int InnerLimit = OuterLimit - MODSTEPDISTANCE;
		
		Double MinGrad = Math.tan( Arg*Math.PI/180 );
		Double MaxGrad = Math.tan( (Arg-ARGSTEP)*Math.PI/180 );
	}
}
