/**
 * 
 */
package mapeditor.view;

import java.awt.GridLayout;
import java.util.HashMap;
import java.util.Vector;

import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * @author Guibrush
 *
 */
public class ChangeParametersPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private HashMap<String, String> _parameters;
	
	private Vector<JTextField> _parametersNames;
	
	private Vector<JTextField> _parametersValues;
	
	public ChangeParametersPanel(HashMap<String, String> initialParameters) {
		
		_parameters = initialParameters;
		
		_parametersNames = new Vector<JTextField>();
		
		_parametersValues = new Vector<JTextField>();
		
		setLayout(new GridLayout(0, 2));
		
		for (String name : _parameters.keySet()) {
			
			JTextField textName = new JTextField();
			textName.setText(name);
			add(textName);
			_parametersNames.add(textName);
			
			JTextField textValue = new JTextField();
			textValue.setText(_parameters.get(name));
			add(textValue);
			_parametersValues.add(textValue);
			
		}
		
		for (int i = 1; i <= 5; i++) {
			
			JTextField textName = new JTextField();
			add(textName);
			_parametersNames.add(textName);
			
			JTextField textValue = new JTextField();
			add(textValue);
			_parametersValues.add(textValue);
			
		}
		
	}
	
	public HashMap<String, String> getParameters() {
		
		HashMap<String, String> parameters = new HashMap<String, String>();
		
		for (int i = 0; i < _parametersNames.size(); i++) {
			
			if (!_parametersNames.get(i).getText().replace(" ", "").equals("") && !_parametersValues.get(i).getText().replace(" ", "").equals(""))
				parameters.put(_parametersNames.get(i).getText(), _parametersValues.get(i).getText());
			
		}
		
		return parameters;
		
	}

}
