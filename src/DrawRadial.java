import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

public class DrawRadial extends JPanel{

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.BLACK);
		g.drawRect(10, 10, 100, 100);
		System.out.println("X");
		
	}
}
