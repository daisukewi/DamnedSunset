/**
 * 
 */
package mapeditor.view;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * @author Guibrush
 *
 */
public class NewElementPanel extends JPanel implements ActionListener, KeyListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JLabel _labelType, _labelColor, _labelSize, _labelHeight, _labelWidth;
	
	private JTextField _textType, _textHeight, _textWidth;
	
	private JButton _buttonChooseColor;
	
	private JPanel _panelColor, _panelCurrentColor, _panelSize;
	
	private boolean _size;
	
	public NewElementPanel(String newElementName, Color initialColor, boolean size) {
		
		_size = size;
		
		setLayout(new GridLayout(0, 2));
		
		_labelType = new JLabel("Introduce el nombre de la nueva " + newElementName + " : ");
		add(_labelType);
		
		_textType = new JTextField();
		add(_textType);
		
		_labelColor = new JLabel("Elige el color:");
		add(_labelColor);
		
		_panelColor = new JPanel();
		add(_panelColor);
		
		_buttonChooseColor = new JButton("Elegir");
		_buttonChooseColor.addActionListener(this);
		_panelColor.add(_buttonChooseColor);
		
		_panelCurrentColor = new JPanel();
		_panelCurrentColor.setBackground(initialColor);
		_panelColor.add(_panelCurrentColor);
		
		if (_size) {
			
			_labelSize = new JLabel("Elige el tamaño:");
			add(_labelSize);
			
			_panelSize = new JPanel();
			_panelSize.setLayout(new GridLayout(0, 4));
			add(_panelSize);
			
			_labelHeight = new JLabel("Altura: ");
			_panelSize.add(_labelHeight);
			
			_textHeight = new JTextField();
			_textHeight.addKeyListener(this);
			_panelSize.add(_textHeight);
			
			_labelWidth = new JLabel("Anchura: ");
			_panelSize.add(_labelWidth);
			
			_textWidth = new JTextField();
			_textWidth.addKeyListener(this);
			_panelSize.add(_textWidth);
			
		}
		
	}
	

	@Override
	public void actionPerformed(ActionEvent e) {
		
		Color color = JColorChooser.showDialog(this, "Elige el color", _panelCurrentColor.getBackground());
		
		if (color != null)
			_panelCurrentColor.setBackground(color);
		
	}
	
	@Override
	public void keyTyped(KeyEvent e) {
		
		if (Character.isDigit(e.getKeyChar())) {
			
			JTextField text = (JTextField) e.getComponent();
			
			if (!text.getText().equals("")) {
				
				int n = Integer.valueOf(text.getText() + Character.toString(e.getKeyChar()));
			
				if ((n > 99) || (n == 0))
					e.consume();
				
			}
			else
				if (Integer.valueOf(Character.toString(e.getKeyChar())) <= 0)
					e.consume();
			
		}
		else
			e.consume();
		
	}


	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
			
	}


	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public String getTypeName() {
		
		return _textType.getText();
		
	}
	
	public Color getTypeColor() {
		
		return _panelCurrentColor.getBackground();
		
	}
	
	public int getEntityHeight() {
		
		if (_size)
			return Integer.valueOf(_textHeight.getText());
		else
			return -1;
		
	}
	
	public int getEntityWidth() {
		
		if (_size)
			return Integer.valueOf(_textWidth.getText());
		else
			return -1;
		
	}

}
