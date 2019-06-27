import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.concurrent.TimeUnit;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;

public class POVDisplay extends JFrame implements ActionListener{
	
	static final int SIZE = 400;
	static final int MODSTEPS = 14;
	static final double MODSTEPDISTANCE = SIZE / (2* MODSTEPS); //Modsteps go out from center
	
	static final int ARGSTEPS = 180;
	static final double ARGSTEP = 360/ARGSTEPS;
	
	int[][][] radialImage;
	BufferedImage ConvertedImage;
	BufferedImage originalImage = new BufferedImage(400, 400, BufferedImage.TYPE_INT_ARGB);;
	
	UI userInterface;
	
	public static void main( String[] args) {
		POVDisplay g = new POVDisplay();
		
		/*
		BufferedImage convert = null;
		try {
			convert = ImageIO.read( new File ("../Images/ExampleStartImage.png"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		int[][][] radial = g.squareToRadial(convert);
		g.drawRadial(radial);*/
	}
	
	public POVDisplay() {
		super();
		this.setSize(800, 600);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);

		userInterface = new UI(this);
		this.add(userInterface);
		
		
		this.setVisible(true);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == userInterface.Search) {		
			String filePath = userInterface.selectFile();
			if(filePath != null) {
				try {
					BufferedImage Image = ImageIO.read(new File(filePath));
					java.awt.Image temp = Image.getScaledInstance(400, 400, Image.SCALE_SMOOTH);
					
					originalImage = new BufferedImage(400, 400, BufferedImage.TYPE_INT_ARGB);;
					System.out.println(Image.getHeight());
				    Graphics2D g2d = originalImage.createGraphics();
				    g2d.drawImage(temp, 0, 0, null);
				    g2d.dispose();
					
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				userInterface.startImage = originalImage;
				userInterface.updateInputImage();
				repaint();
			}

		} else if(e.getSource() == userInterface.Convert) {
			userInterface.sayConverting();
			this.paint(this.getGraphics());
			
			squareToRadial(originalImage);
			drawRadial(radialImage);
			userInterface.finalImage = ConvertedImage;
			userInterface.updateOutputImage();
			this.paint(this.getGraphics());
		}
	}
	
	public int[][][] squareToRadial(BufferedImage Squareimg) {
		
		radialImage = new int[3][ARGSTEPS][MODSTEPS];

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
		ConvertedImage = new BufferedImage( 400, 400, BufferedImage.TYPE_3BYTE_BGR);
		
		for (int Arg = 0; Arg < ARGSTEPS; Arg++) {	
			for (int Mod  = 0; Mod < MODSTEPS; Mod++) {	
				
				int SegmentColor = (Inputimg[0][Arg][Mod] << 16 | Inputimg[1][Arg][Mod] << 8 | Inputimg[2][Arg][Mod]);
				
				for (int x = 0; x < 400; x++) {
					for (int y = 0; y < 400; y++) {
						if( ValidPos( x - 200, 200-y, Arg, Mod)) {
							ConvertedImage.setRGB(x, y, SegmentColor);
						}
					}
				}
			}
		}
		System.out.println("Starting writing");
		File Output = new File("../Images/outputImage" + ".jpg");
		try {
			ImageIO.write(ConvertedImage, "jpg", Output);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	//Old function to manually enter the image into arduino code
	public void imgtoWrittenArray(int[][][] Inputimg) {
		String Img = "{ ";
		for(int[][] level1 : Inputimg) {
			Img +="\n {";
			for(int[] level2: level1) {
				Img += "\n { ";
				for(int level3: level2) {
					Img += level3 + ", ";
				}
				Img = Img.substring(0, Img.length() - 2);
				Img += " },";
			}
			Img = Img.substring(0, Img.length() - 1);
			Img += " },";
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