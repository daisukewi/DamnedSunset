/**
 * 
 */
package mapeditor.view;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import mapeditor.controler.System;
import mapeditor.util.CellType;
import mapeditor.util.ControllerListener;
import mapeditor.util.ElementType;
import mapeditor.util.EntityType;
import mapeditor.util.Position;

/**
 * @author Guibrush
 *
 */
public class InfoPanel extends JPanel implements ControllerListener, ActionListener {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel _headPanel, _parametersPanel, _buttonsPanel;
	private JLabel _labelCellType, _labelEntityMessage, _labelEmpty;
	private JButton _buttonChangeEntity, _buttonRemoveEntity;
	private String _cellType, _entityMessage;
	private Vector<LabelParameter> _selectedEntityParameters;
	private System _system;

	public InfoPanel(System system) {
		
		super();
		
		_system = system;
		
		_cellType = null;
		_entityMessage = null;
		
		_selectedEntityParameters = new Vector<LabelParameter>();
		
		setLayout(new BorderLayout());
		
		_headPanel = new JPanel();
		_headPanel.setLayout(new BoxLayout(_headPanel, BoxLayout.Y_AXIS));
		add(_headPanel, BorderLayout.NORTH);
		
		_labelEmpty = new JLabel(" ");
		_labelEmpty.setAlignmentX(Component.CENTER_ALIGNMENT);
		_headPanel.add(_labelEmpty);
		
		_labelCellType = new JLabel();
		_labelCellType.setAlignmentX(Component.CENTER_ALIGNMENT);
		_headPanel.add(_labelCellType);
		
		_labelEmpty = new JLabel(" ");
		_labelEmpty.setAlignmentX(Component.CENTER_ALIGNMENT);
		_headPanel.add(_labelEmpty);
		
		_labelEntityMessage = new JLabel();
		_labelEntityMessage.setAlignmentX(Component.CENTER_ALIGNMENT);
		_headPanel.add(_labelEntityMessage);
		
		_parametersPanel = new JPanel();
		_parametersPanel.setLayout(new GridLayout(0, 2));
		add(_parametersPanel, BorderLayout.CENTER);
		
		_buttonsPanel = new JPanel();
		add(_buttonsPanel, BorderLayout.SOUTH);
		
		_buttonChangeEntity = new JButton("Cambiar parámetros");
		_buttonChangeEntity.addActionListener(this);
		_buttonsPanel.add(_buttonChangeEntity);
		
		_buttonRemoveEntity = new JButton("Borrar entidad");
		_buttonRemoveEntity.addActionListener(this);
		_buttonsPanel.add(_buttonRemoveEntity);
		
		setEntityButtonsVisible(false);
		
	}
	
	protected void paintComponent(Graphics g) {
		
		super.paintComponent(g);
		
		_labelCellType.setText(_cellType);
		_labelEntityMessage.setText(_entityMessage);
		
		if (!_selectedEntityParameters.isEmpty()) {
			
			for (LabelParameter label : _selectedEntityParameters) {
				
				if (!label.isExist()) {
					
					_parametersPanel.add(label.getLabel());
					label.getLabel().setText(label.getText());
					label.setExist(true);
					
				}
				
			}
			
			setEntityButtonsVisible(true);
			
		}
		else {
			
			setEntityButtonsVisible(false);
			
			_parametersPanel.removeAll();
			
		}
		
	}
	
	private void setEntityButtonsVisible(boolean visible) {
		
		_buttonChangeEntity.setVisible(visible);
		_buttonRemoveEntity.setVisible(visible);
		
	}
	
	private void deSelectCell() {
		
		_cellType = null;
		_entityMessage = null;
		
		_selectedEntityParameters.clear();
		
		_parametersPanel.removeAll();
		
	}

	@Override
	public void cellSelected(Position cell) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showCellType(String cellType) {
		
		_cellType = cellType;
		
		repaint();
	}

	@Override
	public void showEntityMessage(String message) {
		
		_entityMessage = message;
		
		repaint();
		
	}

	@Override
	public void showEntityParameter(String name, String value) {
		
		_selectedEntityParameters.add(new LabelParameter(name, false));
		_selectedEntityParameters.add(new LabelParameter(value, false));
		
		repaint();
		
	}
	
	@Override
	public void cellChanged(Position cell, CellType cellType) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void newMap(int width, int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void cellDeSelected() {
		
		deSelectCell();
		
		repaint();
		
	}

	@Override
	public void preferencesChanged() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void typeElementSelected(ElementType elementType, int height, int width) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void typeElementDeSelected() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void newEntity(Position[] posList, EntityType entityType) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void removeEntity(Position[] posList) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		
		if (e.getActionCommand().equals("Borrar entidad"))
			_system.removeEntity();
		else
			if (e.getActionCommand().equals("Cambiar parámetros")) {
				
				ChangeParametersPanel changeEntityParametersPanel = new ChangeParametersPanel(_system.getEntityParameters());
				
				int val = JOptionPane.showConfirmDialog(this, changeEntityParametersPanel, "Parámetros de la entidad seleccionada", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
				
				if (val == JOptionPane.OK_OPTION)
					_system.setEntityParameters(changeEntityParametersPanel.getParameters());
				
			}
		
	}

}
