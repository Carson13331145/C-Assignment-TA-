import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.event.*;

public class SuperAI
{
	public static void main(String[] args)
	{
		SimpleFrame frame = new SimpleFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.show();
	}
}

class AboutFrame extends JFrame
{
	public AboutFrame()
	{
		setSize(400, 300);
		setResizable(false);
		setTitle("About");
		Toolkit tk = Toolkit.getDefaultToolkit();
		Image ff = tk.getImage("false.gif");
		setIconImage(ff);
		Dimension screenSize = tk.getScreenSize();
		setLocation((screenSize.width-400)/2, (screenSize.height-300)/2);
		FontPanel fpanel = new FontPanel();
		Container con = getContentPane();
		con.add(fpanel);
	}
}

class FontPanel extends JPanel
{
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		Font f = new Font("Serif", Font.BOLD, 22);
		g.setFont(f);
		g.drawString("Super AI", 10, 30);
		f = new Font("Serif", Font.PLAIN, 18);
		g.setFont(f);
		g.drawString("Designer: Alphago", 10, 120);
		g.drawString("The program has been protected.", 10, 225);
		g.drawString("Without permission, no copy is allowed!", 10, 250);
	}
}

class SimpleFrame extends JFrame
{
	public SimpleFrame()
	{
		setSize(WIDTH, HEIGHT);
		setResizable(false);
		setTitle("Super-AI (10*10)");
		Toolkit tk = Toolkit.getDefaultToolkit();
		Image img = tk.getImage("map.gif");
		setIconImage(img);
		Dimension screenSize = tk.getScreenSize();
		setLocation((screenSize.width-WIDTH)/2, (screenSize.height-HEIGHT)/2);

		final AboutFrame aboutFrame = new AboutFrame();

		ImagePanel panel = new ImagePanel();
		Container contentPanel = getContentPane();
		contentPanel.add(panel);

		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);

		JMenu gameMenu = new JMenu("Game(G)");
		gameMenu.setMnemonic('G');

		// Create the sub menu of game and action-listener
		JMenuItem replayItem = new JMenuItem("Replay", 'R');
		replayItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_R, InputEvent.CTRL_MASK));
		replayItem.addActionListener(new AbstractAction("Replay")
		{
			public void actionPerformed(ActionEvent event)
			{
				ImagePanel.restart();
			}
		});
		JMenuItem exitItem = new JMenuItem("Exit", 'E');
		exitItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, InputEvent.CTRL_MASK));
		exitItem.addActionListener(new AbstractAction("EXIT")
		{
			public void actionPerformed(ActionEvent event)
			{
				System.exit(0);
			}
		});
		gameMenu.add(replayItem);
		gameMenu.addSeparator();
		gameMenu.add(exitItem);
		menuBar.add(gameMenu);

		JMenu helpMenu = new JMenu("Help(H)");
		helpMenu.setMnemonic('H');
		JMenuItem aboutItem = new JMenuItem("About", 'A');
		aboutItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, InputEvent.CTRL_MASK));
		aboutItem.addActionListener(new AbstractAction("About")
		{
			public void actionPerformed(ActionEvent event)
			{
				aboutFrame.show();
			}
		});
		helpMenu.add(aboutItem);
		menuBar.add(helpMenu);
	}

	public static final int WIDTH = 560;
	public static final int HEIGHT = 450;

}

final class ImagePanel extends JPanel
{
	public ImagePanel()
	{
		image = Toolkit.getDefaultToolkit().getImage("map.gif");
		green = Toolkit.getDefaultToolkit().getImage("green.gif");
		red = Toolkit.getDefaultToolkit().getImage("red.gif");
		position = Toolkit.getDefaultToolkit().getImage("position.gif");
		ired = Toolkit.getDefaultToolkit().getImage("ired.gif");
		MediaTracker tracker = new MediaTracker(this);
		tracker.addImage(image, 1);  // chess map
		tracker.addImage(green, 2);  // green chess
		tracker.addImage(red, 3);  // red chess
		tracker.addImage(position, 4);  // mouse position
		tracker.addImage(ired, 5);
		try
		{
			tracker.waitForID(1);
			tracker.waitForID(2);
			tracker.waitForID(3);
			tracker.waitForID(4);
			tracker.waitForID(5);
		}
		catch (InterruptedException exception) {}

		// register action-listener
		addMouseListener(new MouseHandler());
		addMouseMotionListener(new MouseMotionHandler());

		// Initialize the chess map
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				ball[i][j] = 0;
		// Set the win positions in X
		for (i = 0; i < 10; i++)
			for (j = 0; j < 6; j++)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[j+k][i][count] = true;
					ctable[j+k][i][count] = true;
				}
				count++;
			}
		// Set the win positions in Y
		for (i = 0; i < 10; i++)
			for (j = 0; j < 6; j++)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[i][j+k][count] = true;
					ctable[i][j+k][count] = true;
				}
				count++;
			}
		// Set other win positions
		for (i = 0; i < 6; i++)
			for (j = 0; j < 6; j++)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[j+k][i+k][count] = true;
					ctable[j+k][i+k][count] = true;
				}
				count++;
			}
		for (i = 0; i < 6; i++)
			for (j = 9; j >= 4; j--)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[j-k][i+k][count] = true;
					ctable[j-k][i+k][count] = true;
				}
				count++;
			}
		computer = false;
		player = true;
	}

	// draw the window panel
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		int FrameWidth = getWidth();
		int FrameHeight = getHeight();
		int x = (FrameWidth - 400)/2;
		int y = FrameHeight - 400;
		int px = mousex - (mousex - x) % 40;
		int py = mousey - (mousey - y) % 40;
		if (px < x) px = x;
		if (py < y) py = y;
		if (px > (x + 360)) px = x + 360;
		if (py > (y + 360)) py = y + 360;
		g.drawImage(image, x, y, null);
		g.drawImage(position, px, py, null);
		Font f = new Font("Serif", Font.BOLD, 20);
		g.setFont(f);
		g.setColor(new Color(204, 66, 204));
		g.drawString("    AI", 5, 60);
		g.setColor(new Color(00, 99, 00));
		g.drawString(" You", 495, 60);
		g.drawImage(red, 20, 75, null);
		g.drawImage(green, 500, 75, null);
		g.setColor(Color.black);

		switch (str)
		{
			case 0:
			g.drawString("You first!", 480, 140);
			break;
			case 1:
			g.drawString("Wait...", 480, 140);
			break;
			case 2:
			g.drawString("Your turns...", 480, 140);
			break;
			case 3:
			g.drawString("You win!", 480, 140);
			break;
			case 4:
			g.drawString("You lose!", 480, 140);
			break;
			case 5:
			g.drawString("Tie!", 480, 140);
			break;
		}

		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
			{
				px = i * 40 + 3 + x;
				py = j * 40 + 3 + y;
				if (ball[i][j] == 1)
					g.drawImage(green, px, py, null);
				if (ball[i][j] == 2)
					g.drawImage(red, px, py, null);
			}
		g.drawImage(ired, a * 40 + x + 3, b * 40 + y + 3, null);
	}

	// Variable
	private Image image, position, green, red, ired;
	private int mousex, mousey;
	private JButton replayButton;

	private static int ball[][] = new int[10][10];
	private static boolean ptable[][][] = new boolean[10][10][192];
	private static boolean ctable[][][] = new boolean[10][10][192];
	private static int pgrades[][] = new int[10][10];
	private static int cgrades[][] = new int[10][10];
	private static int pgrade, cgrade;
	private static int win[][] = new int[2][192];
	private static int pcount, ccount;
	private static boolean player, computer, start = true, over = false;
	private static boolean pwin, cwin, tie;
	private static int i, j, k, n, m, count, a = 50, b = 50;
	private static int mat, nat, mde, nde;
	private static int str = 0;

	private class replayAction implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			restart();
		}
	}

	private class MouseMotionHandler implements MouseMotionListener
	{
		public void mouseMoved(MouseEvent event)
		{
			mousex = event.getX();
			mousey = event.getY();
			repaint();
		}
		public void mouseDragged(MouseEvent event) {}
	}

	private class MouseHandler extends MouseAdapter
	{
		public void mousePressed(MouseEvent event)
		{
			mousex = event.getX();
			mousey = event.getY();

			if (!over && player)
			{
				int FrameWidth = getWidth();
				int FrameHeight = getHeight();
				int x = (FrameWidth - 400) / 2;
				int y = FrameHeight - 400 - 5;
				if (mousex > x && mousex < (x + 400) &&
					mousey > y && mousey < (y + 400))
				{
					m = (int)((mousex - x) / 40);
					n = (int)((mousey - y) / 40);
					while (ball[m][n] == 0)
					{
						ball[m][n] = 1;
						pcount++;
						str = 1;
						if ((ccount == 50) && (pcount == 50))
						{
							tie = over = true;
							str = 5;
						}
						for (i = 0; i < 192; i++)
						{
							if (ptable[m][n][i] && win[0][i] != 7)
								win[0][i]++;
							if (ctable[m][n][i])
							{
								ctable[m][n][i] = false;
								win[1][i] = 7;
							}
						}
						if (!over)
						{
							for (i = 0; i <= 1; i++)
								for (j = 0; j < 192; j++)
								{
									if (win[i][j] == 5)
										// Player win
										if (i == 0)
										{
											pwin = over = true;
											cwin = false;
											str = 3;
											break;
										}
										// Computer win
										else
										{
											cwin = over = true;
											pwin = false;
											str = 4;
											break;
										}
									if (over) break;
								}
						}
						player = false;
						computer = true;
						repaint();
						if (over)
						{
							if (tie)
								JOptionPane.showConfirmDialog(
									ImagePanel.this, "Tie!", "Confirm info",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							else
								if (pwin)
									JOptionPane.showConfirmDialog(
										ImagePanel.this, "Congratualaion! You win.",
										"Confirm info", JOptionPane.DEFAULT_OPTION,
										JOptionPane.INFORMATION_MESSAGE);
								else if (cwin)
									JOptionPane.showConfirmDialog(
										ImagePanel.this, "You lose!", "Confirm info",
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.INFORMATION_MESSAGE);
							restart();
						}
					}
				}
			}
			computerdo();
		}
	}

	public void computerdo()
	{
		if (!over)
			if (computer)
			{
				// Count the score for player
				for (i = 0; i <= 9; i++)
					for (j = 0; j <= 9; j++)
					{
						pgrades[i][j] = 0;
						if (ball[i][j] == 0)
							for (k = 0; k < 192; k++)
								if (ptable[i][j][k])
								{
									switch (win[0][k])
									{
										case 1:
										pgrades[i][j] += 5;
										break;
										case 2:
										pgrades[i][j] += 50;
										break;
										case 3:
										pgrades[i][j] += 100;
										break;
										case 4:
										pgrades[i][j] += 400;
										break;
									}
								}
					}
				// Count the score for computer
				for (i = 0; i <= 9; i++)
					for (j = 0; j <= 9; j++)
					{
						cgrades[i][j] = 0;
						if (ball[i][j] == 0)
							for (k = 0; k < 192; k++)
								if (ctable[i][j][k])
								{
									switch(win[1][k])
									{
										case 1:
										cgrades[i][j] += 5;
										break;
										case 2:
										cgrades[i][j] += 50;
										break;
										case 3:
										cgrades[i][j] += 100;
										break;
										case 4:
										cgrades[i][j] += 400;
										break;
									}
								}
					}
					if (start)
					{
						if (ball[4][4] == 0)
						{
							m = 4;
							n = 4;
						}
						else
						{
							m = 5;
							n = 5;
						}
						start = false;
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
								if (ball[i][j] == 0)
								{
									if (cgrades[i][j] >= cgrade)
									{
										cgrade = cgrades[i][j];
										mat = i;
										nat = j;
									}
									if (pgrades[i][j] >= pgrade)
									{
										pgrade = pgrades[i][j];
										mde = i;
										nde = j;
									}
								}
								// Defend
								if (pgrade >= cgrade && pgrade > 100)
								{
									m = mde;
									n = nde;
								}
								// Attack
								else
								{
									m = mat;
									n = nat;
								}
					}
					cgrade = pgrade = 0;
					ball[m][n] = 2;
					a = m;
					b = n;
					ccount++;
					str = 2;
					if ((ccount == 50) && (pcount == 50))
					{
						tie = over = true;
					}
					for (i = 0; i < 192; i++)
					{
						if (ctable[m][n][i] && win[1][i] != 7)
							win[1][i]++;
						if (ptable[m][n][i])
						{
							ptable[m][n][i] = false;
							win[0][i] = 7;
						}
					}
					if (!over)
					{
						for (i = 0; i <=1; i++)
							for (j = 0; j < 192; j++)
							{
								if (win[i][j] == 5)
									// Player win
									if (i == 0)
									{
										pwin = over = true;
										cwin = false;
										str = 3;
										break;
									}
									else
									{
										cwin = over = true;
										pwin = false;
										str = 4;
										break;
									}
								if (over) break;
							}
						}
						player = true;
						computer = false;
						repaint();
						if (over)
						{
							if (tie)
								JOptionPane.showConfirmDialog(
									ImagePanel.this,
									"Tie!", "Confirm info",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							else
								if (pwin)
									JOptionPane.showConfirmDialog(
										ImagePanel.this,
										"Congratualaion! You win.",
										"Confirm info",
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.INFORMATION_MESSAGE);
								else if (cwin)
									JOptionPane.showConfirmDialog(
									ImagePanel.this,
									"You lose!", "Confirm info",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							restart();
						}
			}
	}

	public static void restart()
	{
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
			{
				pgrades[i][j] = 0;
				cgrades[i][j] = 0;
				ball[i][j] = 0;
			}
		count = 0;
		// Set the X-win
		for (i = 0; i < 10; i++)
			for (j = 0; j < 6; j++)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[j+k][i][count] = true;
					ctable[j+k][i][count] = true;
				}
				count++;
			}
		// Set the Y-win
		for (i = 0; i < 10; i++)
			for (j = 0; j < 6; j++)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[i][j+k][count] = true;
					ctable[i][j+k][count] = true;
				}
				count++;
			}
		// Set the other win
		for (i = 0; i < 6; i++)
			for (j = 0; j < 6; j++)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[j+k][i+k][count] = true;
					ctable[j+k][i+k][count] = true;
				}
				count++;
			}
		for (i = 0; i < 6; i++)
			for (j = 9; j >= 4; j--)
			{
				for (k = 0; k < 5; k++)
				{
					ptable[j-k][i+k][count] = true;
					ctable[j-k][i+k][count] = true;
				}
				count++;
			}
		for (i = 0; i <= 1; i++)
			for (j = 0; j < 192; j++)
				win[i][j] = 0;
		computer = false;
		player = true;
		str = count = ccount = pcount = 0;
		start = true;
		over = pwin = cwin = tie = false;
		a = b = 50;
	}

}
