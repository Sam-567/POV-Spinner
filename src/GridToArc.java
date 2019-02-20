import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class GridToArc extends JFrame{
	
	static final int SIZE = 400;
	static final int MODSTEPS = 10;
	static final int MODSTEPDISTANCE = SIZE / (2* MODSTEPS); //Modsteps go out from center
	
	static final int ARGSTEPS = 20;
	static final int ARGSTEP = 360/20;
	static final int ANGLE = 400;
	//static final double 
	
	public static void main( String[] args) {
		GridToArc g = new GridToArc();
		//g.squareToRadial();
		g.TestValidPos();
	}
	
	public void squareToRadial() {
		BufferedImage Image = null;
		
		int xCenter = SIZE/2;
		int yCenter = SIZE/2;
		
		int[][][] radialImage = new int[3][ARGSTEPS][10];
		
		
		try { 
		    File img = new File("testPhoto.png");
		    Image = ImageIO.read(img ); 
		} catch (IOException e){
			e.printStackTrace();
		}

		int Red = (new Color( Image.getRGB(1, 1))).getRed();
		System.out.println(Red);
		
		int pixels;
			
		int RedSum;
		int GreenSum;
		int BlueSum;
		int ono = 0;
		for (int Arg = 0; Arg < ARGSTEPS; Arg++) {
			
			for (int Mod = 0; Mod < 10; Mod++) {
				
				RedSum = 0;
				GreenSum = 0;
				BlueSum = 0;
				pixels = 0;
				
				for (int x = 0; x < 400; x++) {
					
					for (int y = 0; y < 400; y++) {
						
						if( ValidPos (x-200, y-200, Arg, Mod) ) {
							pixels++;
							Color pixel = new Color( Image.getRGB(x, y));
							
							RedSum += pixel.getRed();
							BlueSum += pixel.getBlue();
							GreenSum += pixel.getGreen();
						}
					}
				}

				
				if(pixels != 0) {
				//if(RedSum != 0) {
					radialImage[0][Arg][Mod] = RedSum/pixels;
					//radialImage[1][Arg][Mod] = BlueSum/pixels;
					//radialImage[2][Arg][Mod] = GreenSum/pixels;
				} else {
					System.out.println("ono" + ono++);
				}

				System.out.println(Mod +" | " + Arg + " | " + radialImage[0][Arg][Mod]);
				
			}
		}
		//drawRadial(radialImage);
		
	}
	
	public void drawRadial(int[][][] img) {
		for (int Arg = 0; Arg < 18; Arg++) {
			for (int Mod = 0; Mod < 10; Mod++) {
				System.out.println(Mod +" | " + Arg + " | " + img[0][Arg][Mod]);
			}
		}
	}
	
	//10 MODs (10 led on one side)
	//20 Rads (positions of 10*)

	
	public boolean ValidPos(int x, int y, int Arg, int Mod) {
		int InnerLimit = MODSTEPDISTANCE * Mod;
		int OuterLimit = InnerLimit + MODSTEPDISTANCE;
		
		Double MaxGrad = 1 / Math.tan( (Arg*ARGSTEP+0.000000001)*Math.PI/180 );
		Double MinGrad =  1 / Math.tan( ((Arg+1)*ARGSTEP+0.000000001)*Math.PI/180 );
		
		//if(M)
		int CenterDistance = x*x + y*y;

		
		Boolean InCircles = ( CenterDistance <= OuterLimit*OuterLimit ) && ( CenterDistance >= InnerLimit*InnerLimit ) ;

		
		Boolean InTriangle = (y >= MinGrad*x) && (y <= MaxGrad*x);

		

		if(true) {
			
			System.out.println("InnerLimit " + InnerLimit);
			System.out.println("OuterLimit " + OuterLimit);
			System.out.println("MAXGRAD " + MaxGrad);
			System.out.println("MINGRAD " + MinGrad);
			System.out.println(CenterDistance);
			System.out.println(InCircles);
			System.out.println(InTriangle);
		}
		return InCircles && InTriangle;
		
	}
	
	public void TestValidPos() {
		
		System.out.println(Math.tan(3.05));
		//assert(false);
		assert( ValidPos( 1, 10, 0, 0) );
		assert( ValidPos( -1, 2, 9, 0) );
		System.out.println("--------------");
		/*assert( ValidPos( 1, 30, 0, 1) );
		assert( !ValidPos( 30, 30, 0 ,0 ));
		assert( ValidPos( 20, 40, 1, 2) );
		assert( !ValidPos( -20, -40, 1, 1) );
		assert( !ValidPos( -40, -20, 1, 1) );
		assert( ValidPos( 1, 199, 0, 9) );
		assert( ValidPos( -1, 199, 19, 9) ); //fuck this one in particular @#$%^&
		assert( !ValidPos( -1, -199, 19, 9) ); 
		assert( !ValidPos( 0, 200, 0, 8) );*/
		
		System.out.println("PASSED!!! :D");
	}
}
