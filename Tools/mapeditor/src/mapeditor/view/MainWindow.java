/**
 * 
 */
package mapeditor.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.filechooser.FileNameExtensionFilter;

import mapeditor.controler.System;
import mapeditor.util.CellType;
import mapeditor.util.ControllerListener;
import mapeditor.util.ElementType;
import mapeditor.util.EntityType;
import mapeditor.util.Position;

/**
 * 
 * @author Guibrush
 */
public class MainWindow implements ComponentListener, WindowListener, ControllerListener {
	
	private JFrame _window;
	private JScrollPane _mapPanelWrapper;
	private JMenuBar _menu;
	private JMenu _menuMap, _menuCell, _menuEntity;
	private JMenuItem _menuNewMap, _menuSaveMap, _menuOpenMap, _menuExportMap, _menuImportMap, _menuNewCellType, _menuNewEntityType, _menuChangeCellParameters, _menuChangeMapParameters;
	private JFileChooser _fileChooser;
	private PalettePanel _palettePanel;
	private MapPanel _mapPanel;
	private InfoPanel _infoPanel;
	private System _system;
	
	public MainWindow(System system) {
		
		_fileChooser = new JFileChooser(java.lang.System.getProperty("user.dir"));
		_fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Archivos de mapa", "map"));
		_fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Archivos de mapa en lua", "lua"));
		
		_system = system;
		
		system.addListener(this);
		
		_window = new JFrame("Damned Sunset - Map Editor");
		_window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		_window.setLayout(new BorderLayout());
		_window.addComponentListener(this);
		_window.addWindowListener(this);
		
		_palettePanel = new PalettePanel(system);
		system.addListener(_palettePanel);
		
		_window.add(_palettePanel, BorderLayout.WEST);
		
		_mapPanelWrapper = new JScrollPane();
		
		_mapPanel = new MapPanel(10, system);
		system.addListener(_mapPanel);
		_mapPanelWrapper.setViewportView(_mapPanel);
		
		_window.add(_mapPanelWrapper, BorderLayout.CENTER);
		
		_infoPanel = new InfoPanel(system);
		system.addListener(_infoPanel);
		
		_window.add(_infoPanel, BorderLayout.EAST);
		
		_menu = new JMenuBar();
		_window.setJMenuBar(_menu);
		
		_menuMap = new JMenu("Mapa");
		_menu.add(_menuMap);
		
		_menuNewMap = new JMenuItem("Nuevo Mapa");
		_menuNewMap.addActionListener(new NewMapMenuListener());
		_menuMap.add(_menuNewMap);
		
		_menuSaveMap = new JMenuItem("Guardar Mapa");
		_menuSaveMap.addActionListener(new SaveMapMenuListener());
		_menuMap.add(_menuSaveMap);
		
		_menuOpenMap = new JMenuItem("Abrir Mapa");
		_menuOpenMap.addActionListener(new OpenMapMenuListener());
		_menuMap.add(_menuOpenMap);
		
		_menuMap.addSeparator();
		
		_menuExportMap = new JMenuItem("Exportar Mapa");
		_menuExportMap.addActionListener(new ExportMapMenuListener());
		_menuMap.add(_menuExportMap);
		
		_menuImportMap = new JMenuItem("Importar Mapa");
		_menuImportMap.addActionListener(new ImportMapMenuListener());
		_menuMap.add(_menuImportMap);
		
		_menuMap.addSeparator();
		
		_menuChangeMapParameters = new JMenuItem("Cambiar parámetros del mapa");
		_menuChangeMapParameters.addActionListener(new ChangeMapParameters());
		_menuMap.add(_menuChangeMapParameters);
		
		_menuCell = new JMenu("Celda");
		_menu.add(_menuCell);
		
		_menuNewCellType = new JMenuItem("Nuevo tipo de celda");
		_menuNewCellType.addActionListener(new NewCellTypeMenuListener());
		_menuCell.add(_menuNewCellType);
		
		_menuChangeCellParameters = new JMenuItem("Cambiar parámetros de la celda");
		_menuChangeCellParameters.addActionListener(new ChangeCellParameters());
		_menuChangeCellParameters.setEnabled(false);
		_menuCell.add(_menuChangeCellParameters);
		
		_menuEntity = new JMenu("Entidad");
		_menu.add(_menuEntity);
		
		_menuNewEntityType = new JMenuItem("Nuevo tipo de entidad");
		_menuNewEntityType.addActionListener(new NewEntityTypeMenuListener());
		_menuEntity.add(_menuNewEntityType);
		
		Dimension d1 = new Dimension(1024, 600);
		_window.setPreferredSize(d1);
		_window.setMinimumSize(d1);
		
		Dimension d2 = new Dimension((_window.getWidth() / 4) * 3, _window.getHeight());
		_mapPanelWrapper.setPreferredSize(d2);
		
		_window.pack();
		
	}
	
	public void show() {
		
		_window.setVisible(true);
		
	}

	@Override
	public void componentResized(ComponentEvent e) {

		Dimension d = new Dimension((_window.getWidth() / 4) * 3, _window.getHeight());
		_mapPanelWrapper.setPreferredSize(d);
		
	}

	@Override
	public void componentMoved(ComponentEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void componentShown(ComponentEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void componentHidden(ComponentEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void windowOpened(WindowEvent e) {
		
		File preferences = new File("preferences.pref");
		
		if (preferences.exists())
			_system.openPreferences(preferences);
		else
			_system.initializePreferences();
		
		_palettePanel.initialize();
		
	}

	@Override
	public void windowClosing(WindowEvent e) {
		
		File preferences = new File("preferences.pref");
		
		try {
			preferences.createNewFile();
			
			_system.savePreferences(preferences);
			
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		
		
	}

	@Override
	public void windowClosed(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowActivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeactivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void cellSelected(Position cell) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void cellDeSelected() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void cellChanged(Position cell, CellType celltype) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void newMap(int width, int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showCellType(String cellType) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showEntityMessage(String message) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showEntityParameter(String name, String value) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void preferencesChanged() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void typeElementSelected(ElementType elementType, int height,
			int width) {
		
		if (elementType instanceof CellType)
			_menuChangeCellParameters.setEnabled(true);
		
	}

	@Override
	public void typeElementDeSelected() {
		
		_menuChangeCellParameters.setEnabled(false);
		
	}

	@Override
	public void newEntity(Position[] posList, EntityType entityType) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void removeEntity(Position[] posList) {
		// TODO Auto-generated method stub
		
	}
	
	class NewMapMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			//_mapPanel.newMap(90, 90, new CellType("Sand"));
			
			NewMapPanel newMapPanel = new NewMapPanel(_system.getPreferencesStringCellTypes());
			
			int val = JOptionPane.showConfirmDialog(_window, newMapPanel, "Nuevo Mapa", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
			
			if (val == JOptionPane.OK_OPTION)
				_mapPanel.newMap(newMapPanel.getMapWidth(), newMapPanel.getMapHeight(), new CellType(newMapPanel.getBasicCell()));
		}
		
	}
	
	class SaveMapMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			if (_system.initialized()) {
				int val = _fileChooser.showSaveDialog(_window);
				
				if (val == JFileChooser.APPROVE_OPTION)
					_system.saveMap(new File(_fileChooser.getSelectedFile().getName() + ".map"));
			}
			else
				JOptionPane.showMessageDialog(_window, "No hay ningún mapa cargado, crea uno nuevo o abre uno existente.");
			
		}
		
	}
	
	class OpenMapMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			int option = JOptionPane.showConfirmDialog(_window, "Se perderán los cambios no guardados en el mapa actual. ¿Quieres continuar?");
			
			if (option == JOptionPane.OK_OPTION) {
				
				int val = _fileChooser.showOpenDialog(_window);
				
				if (val == JFileChooser.APPROVE_OPTION) {
					
					if (_fileChooser.getSelectedFile().getName().endsWith(".map"))
						_system.loadMap(_fileChooser.getSelectedFile());
					else
						JOptionPane.showMessageDialog(_window, "El archivo seleccionado no es de tipo .map. Selecciona un archivo correcto.");
						
				}
				
			}
			
		}
		
	}
	
	class ExportMapMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
				
			if (_system.initialized()) {
				int val = _fileChooser.showSaveDialog(_window);
				
				if (val == JFileChooser.APPROVE_OPTION)
					_system.exportMap(new File(_fileChooser.getSelectedFile().getName() + ".lua"));
			}
			else
				JOptionPane.showMessageDialog(_window, "No hay ningún mapa cargado, crea uno nuevo o abre uno existente.");
			
		}
		
	}
	
	class ImportMapMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			int option = JOptionPane.showConfirmDialog(_window, "Se perderán los cambios no guardados en el mapa actual. ¿Quieres continuar?");
			
			if (option == JOptionPane.OK_OPTION) {
				
				int val = _fileChooser.showOpenDialog(_window);
				
				if (val == JFileChooser.APPROVE_OPTION) {
					
					if (_fileChooser.getSelectedFile().getName().endsWith(".txt"))
						_system.importMap(_fileChooser.getSelectedFile());
					else
						JOptionPane.showMessageDialog(_window, "El archivo seleccionado no es de tipo .txt. Selecciona un archivo correcto.");
						
				}
				
			}
			
		}
		
	}
	
	class NewCellTypeMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			NewElementPanel newCellPanel = new NewElementPanel("Celda", Color.WHITE, false);
			
			boolean ok = false;
			
			while (!ok) {
				
				int val = JOptionPane.showConfirmDialog(_window, newCellPanel, "Nuevo tipo de celda", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
				
				if (val == JOptionPane.OK_OPTION)
					ok = _system.newCellType(newCellPanel.getTypeColor(), newCellPanel.getTypeName());
				else
					ok = true;
				
				if (!ok)
					JOptionPane.showMessageDialog(_window, "El tipo de celda introducido ya existe. Introduce uno nuevo.");
				
			}
			
		}
		
	}
	
	class NewEntityTypeMenuListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			NewElementPanel newCellPanel = new NewElementPanel("Entidad", Color.WHITE, true);
			
			boolean ok = false;
			
			while (!ok) {
				
				int val = JOptionPane.showConfirmDialog(_window, newCellPanel, "Nuevo tipo de entidad", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
				
				if (val == JOptionPane.OK_OPTION)
					ok = _system.newEntityType(newCellPanel.getTypeColor(), newCellPanel.getTypeName(), newCellPanel.getEntityHeight(), newCellPanel.getEntityWidth());
				else
					ok = true;
				
				if (!ok)
					JOptionPane.showMessageDialog(_window, "El tipo de entidad introducido ya existe. Introduce uno nuevo.");
				
			}
			
		}
		
	}
	
	class ChangeCellParameters implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			ChangeParametersPanel changeCellParametersPanel = new ChangeParametersPanel(_system.getCellParameters());
			
			int val = JOptionPane.showConfirmDialog(_window, changeCellParametersPanel, "Parámetros del tipo de celda seleccionado", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
			
			if (val == JOptionPane.OK_OPTION)
				_system.setCellParameters(changeCellParametersPanel.getParameters());
			
		}
		
	}
	
	class ChangeMapParameters implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			
			ChangeParametersPanel changeMapParametersPanel = new ChangeParametersPanel(_system.getMapParameters());
			
			int val = JOptionPane.showConfirmDialog(_window, changeMapParametersPanel, "Parámetros del mapa", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
			
			if (val == JOptionPane.OK_OPTION)
				_system.setMapParameters(changeMapParametersPanel.getParameters());
			
		}
		
	}

}
