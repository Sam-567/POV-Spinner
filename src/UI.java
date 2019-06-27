import java.awt.Dimension;
import java.awt.FileDialog;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;



public class UI extends JPanel{
	
	JFileChooser fileChooser;
	File file ;
	JButton Search;
	JButton Convert;
	JButton Upload;
	GridBagLayout layout = new GridBagLayout();
	GridBagConstraints constraints = new GridBagConstraints();
	BufferedImage startImage;
	BufferedImage finalImage;
	JLabel originalPicture;
	JLabel editedPicture;
	
	public UI(ActionListener listener) {
		super();
		this.setLayout(layout);
		Search = new JButton("Select File");
		Search.addActionListener(listener);
		
		Convert = new JButton("Convert");

        Convert.setSize(new Dimension(400, 50));
		Convert.setEnabled(false);
		Convert.addActionListener(listener);
		
		Upload = new JButton("Upload");
		Upload.setEnabled(false);
		Upload.addActionListener(listener);
		
		try {
			startImage = ImageIO.read(new File("../Images/ExampleStartImage.png"));
			finalImage = ImageIO.read(new File("../Images/ExampleEditedImage.jpg"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		originalPicture = new JLabel(new ImageIcon(startImage));
		editedPicture = new JLabel(new ImageIcon(finalImage));
		
		constraints.gridy = 0;
		constraints.ipady = 20;
		this.add(Search, constraints);

		this.add(Convert, constraints);
		
		constraints.gridwidth = 1;
		constraints.gridy = 1;
		constraints.gridx = 0;
		this.add(originalPicture, constraints);
		
		constraints.gridx = 1;
		this.add(editedPicture, constraints);

	}
	
	public void updateInputImage() {
		originalPicture.setIcon(new ImageIcon(startImage));
		this.remove(Upload);
		constraints.gridy = 0;
		Convert.setText("Convert");
		this.add(Convert, constraints);
		Convert.setEnabled(true);
		this.repaint();
	}
	
	public void updateOutputImage() {
		editedPicture.setIcon(new ImageIcon(finalImage));
		this.remove(Convert);
		constraints.gridy = 0;
		this.add(Upload);
		this.repaint();
	}
	public void sayConverting() {
		Convert.setText("Converting");
		this.repaint();
	}
	public String selectFile() {
		FileDialog directorySearch = new FileDialog(new JFrame(), "Select File to Open");
	    directorySearch.setMode(FileDialog.LOAD);
	    directorySearch.setDirectory("C:\\");
	    directorySearch.setVisible(true);
	    String fileName = directorySearch.getFile();
	    String fileLocation = directorySearch.getDirectory();
	    
	    String path = null;
	    if(fileName != null && fileLocation != null) {
		   path = fileLocation + fileName;
	    }
	    return path;
	}


	
}
