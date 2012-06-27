/**
 * 
 */
package mapeditor.view;

import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * @author Guibrush
 *
 */
public class NewMapPanel extends JPanel implements KeyListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JLabel _labelHeight, _labelWidth, _labelBasicCell;
	private JTextField _textHeight, _textWidth;
	private JComboBox<String> _comboBasicCell;
	
	public NewMapPanel(String[] cells) {
		
		setLayout(new GridLayout(0, 2));
		
		_labelHeight = new JLabel("Altura");
		add(_labelHeight);
		
		_textHeight = new JTextField("90");
		_textHeight.addKeyListener(this);
		add(_textHeight);
		
		_labelWidth = new JLabel("Anchura");
		add(_labelWidth);
		
		_textWidth = new JTextField("90");
		_textWidth.addKeyListener(this);
		add(_textWidth);
		
		_labelBasicCell = new JLabel("Celda inicial");
		add(_labelBasicCell);
		
		_comboBasicCell = new JComboBox<String>(cells);
		add(_comboBasicCell);
		
	}
	
	@Override
	public void keyTyped(KeyEvent e) {
		
		if (Character.isDigit(e.getKeyChar())) {
			
			JTextField text = (JTextField) e.getComponent();
			
			if (!text.getText().equals("")) {
				
				int n = Integer.valueOf(text.getText() + Character.toString(e.getKeyChar()));
			
				if ((n > 200) || (n == 0))
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
	
	public int getMapHeight() {
		
		return Integer.valueOf(_textHeight.getText());
		
	}
	
	public int getMapWidth() {
		
		return Integer.valueOf(_textWidth.getText());
		
	}
	
	public String getBasicCell() {
		
		return (String) _comboBasicCell.getSelectedItem();
		
	}

}
