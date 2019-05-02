import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class GridToArc{
	
	static final int SIZE = 400;
	static final int MODSTEPS = 14;
	static final double MODSTEPDISTANCE = SIZE / (2* MODSTEPS); //Modsteps go out from center
	
	static final int ARGSTEPS = 120;
	static final double ARGSTEP = 360/ARGSTEPS;
	//static final double 
	
	public static void main( String[] args) {
		GridToArc g = new GridToArc();
		//g.squareToRadial();
		//g.TestValidPos();
		//g.ValidPosImg();
		
		BufferedImage convert = null;
		try {
			convert = ImageIO.read( new File ("MarioTest.png"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		int[][][] radial = g.squareToRadial(convert);
		//g.drawRadial(radial);
		g.printImg(radial);
		
	}
	
	public int[][][] squareToRadial(BufferedImage Squareimg) {
		
		int[][][] radialImage = new int[3][ARGSTEPS][MODSTEPS];

		int pixels;
		int RedSum;
		int GreenSum;
		int BlueSum;

		for (int Arg = 0; Arg < ARGSTEPS; Arg++) {
			
			for (int Mod = 0; Mod < MODSTEPS; Mod++) {
				
				RedSum = 0;
				GreenSum = 0;
				BlueSum = 0;
				pixels = 0;
				
				for (int x = 0; x < 400; x++) {
					
					for (int y = 0; y < 400; y++) {
						
						if( ValidPos (x-200, 200-y, Arg, Mod) ) {
							pixels++;
							Color pixel = new Color( Squareimg.getRGB(x, y));
							
							RedSum += pixel.getRed();
							BlueSum += pixel.getBlue();
							GreenSum += pixel.getGreen();
						}
					}
				}
				
				if (pixels != 0) {
					radialImage[0][Arg][Mod] = RedSum/pixels;
					radialImage[1][Arg][Mod] = GreenSum/pixels;
					radialImage[2][Arg][Mod] = BlueSum/pixels;
				}
			}
		}	
		return radialImage;
	}
	
	public void drawRadial(int[][][] Inputimg) {
		BufferedImage Outputimg = new BufferedImage( 400, 400, BufferedImage.TYPE_3BYTE_BGR);
		
		for (int Arg = 0; Arg < ARGSTEPS; Arg++) {	
			for (int Mod  = 0; Mod < MODSTEPS; Mod++) {	
				
				//int SegmentColor = new Color( Inputimg[0][Arg][Mod], Inputimg[1][Arg][Mod], Inputimg[2][Arg][Mod]).getRGB();  
				int SegmentColor = (Inputimg[0][Arg][Mod] << 16 | Inputimg[1][Arg][Mod] << 8 | Inputimg[2][Arg][Mod]);
				
				for (int x = 0; x < 400; x++) {
					for (int y = 0; y < 400; y++) {
						if( ValidPos( x - 200, 200-y, Arg, Mod)) {
							Outputimg.setRGB(x, y, SegmentColor);
						}
					}
				}
			}
		}
		System.out.println("Starting writing");
		File Output = new File("Reality" + ".jpg");
		try {
			ImageIO.write(Outputimg, "jpg", Output);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void printImg(int[][][] Inputimg) {
		String Img = "{ ";
		for(int[][] level1 : Inputimg) {
			Img +="\n {";
			for(int[] level2: level1) {
				Img += "\n { ";
				for(int level3: level2) {
					Img += level3 + ", ";
				}
				Img = Img.substring(0, Img.length() - 1);
				Img += " },";
			}
			Img = Img.substring(0, Img.length() - 1);
			Img += " }, ";
		}
		Img = Img.substring(0, Img.length() - 1);
		Img += " };";
		System.out.println(Img);
	}
	
	public void ValidPosImg() {
		for(int Arg = 0; Arg < ARGSTEPS; Arg++) {
			
			BufferedImage img = new BufferedImage( 400, 400, BufferedImage.TYPE_3BYTE_BGR);
			
			for (int x = 0; x < 400; x++) {
				for (int y = 0; y < 400; y++) {
					for (int mod  = 0; mod < MODSTEPS; mod++) {
						if( ValidPos( x - 200, 200-y, Arg, mod)) {
							
							
							img.setRGB(x, y, Color.ORANGE.getRGB() );
						}
					}
				}
			}
			File Output = new File("Arg " + Arg + ".jpg");
			try {
				ImageIO.write(img, "jpg", Output);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}


	public boolean ValidPos (int x, int y, int Arg, int Mod) {
		double InnerLimit = MODSTEPDISTANCE * Mod;
		double OuterLimit = InnerLimit + MODSTEPDISTANCE;
		
		Double MaxGrad = 1 / Math.tan( (Arg*ARGSTEP+0.0000001)*Math.PI/180 );
		Double MinGrad =  1 / Math.tan( ((Arg+1)*ARGSTEP-0.0000001)*Math.PI/180 );

		
		if ( Arg > ARGSTEPS/2 -1) {
			//Swap the two
			Double temp = MaxGrad;
			MaxGrad = MinGrad;
			MinGrad = temp;
		}
			
				
		int CenterDistance = x*x + y*y;

		Boolean InCircles = ( CenterDistance <= OuterLimit*OuterLimit ) && ( CenterDistance >= InnerLimit*InnerLimit ) ;
		Boolean InTriangle = (y >= MinGrad*x) && (y <= MaxGrad*x);

		return InCircles && InTriangle;
		
	}
	
	
	public void TestValidPos() {
		
		//assert(false);
		assert( ValidPos( 1, 10, 0, 0) );
		assert( ValidPos( -1, 4, 19, 0) );
		assert( ValidPos( 1, -4, 9, 0) );
		assert( ValidPos( -1, -4, 10, 0) );

		assert( ValidPos( 1, 30, 0, 1) );
		assert( !ValidPos( 30, 30, 0 ,0 ));
		assert( ValidPos( 20, 40, 1, 2) );
		assert( !ValidPos( -20, -40, 1, 1) );
		assert( !ValidPos( -40, -20, 1, 1) );
		assert( ValidPos( 1, 199, 0, 9) );
		assert( ValidPos( -1, 199, 19, 9) );
		assert( !ValidPos( -1, -199, 19, 9) ); 
		assert( !ValidPos( 0, 200, 0, 8) );
		
		assert( ValidPos(10, 6, 3, 0) );
		assert( !ValidPos(10, 3, 3, 0) );
		
		assert( ValidPos(-10, 6, 16, 0) );
		assert( !ValidPos(10, -6, 16, 0) );
		
		
		
		
		System.out.println("PASSED!!! :D");
	}
}

//20 == 0 in arg