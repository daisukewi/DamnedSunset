/**
 * 
 */
package mapeditor.view;

import javax.swing.JLabel;

/**
 * @author Guibrush
 *
 */
public class LabelParameter {
	
	private JLabel _label;
	
	private boolean _exist;
	
	private String _text;
	
	public LabelParameter(String text, boolean exist) {
		
		_text = text;
		_exist = exist;
		
		_label = new JLabel();
		
	}

	/**
	 * @return the label
	 */
	public JLabel getLabel() {
		return _label;
	}

	/**
	 * @return the exist
	 */
	public boolean isExist() {
		return _exist;
	}

	/**
	 * @return the text
	 */
	public String getText() {
		return _text;
	}

	/**
	 * @param label the label to set
	 */
	public void setLabel(JLabel label) {
		this._label = label;
	}

	/**
	 * @param exist the exist to set
	 */
	public void setExist(boolean exist) {
		this._exist = exist;
	}

	/**
	 * @param text the text to set
	 */
	public void setText(String text) {
		this._text = text;
	}

}
