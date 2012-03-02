/**
 * 
 */
package mapeditor.view;

import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

import javax.swing.JPanel;
import javax.swing.JViewport;

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
public class MapPanel extends JPanel implements MouseListener, MouseWheelListener, ControllerListener, MouseMotionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * Tamaño en píxeles de cada celda del mapa.
	 */
	private int _grid;
	private int _border;
	private int _zoom;
	private int _width;
	private int _height;
	private Position _selectedCell;
	private mapeditor.controler.System _system;
	private Color[][] _colorCellMap;
	private Color[][] _colorEntityMap;
	private Color _selectedColorEntity;
	private int _selectedEntityHeight, _selectedEntityWidth;
	private int _mouseX, _mouseY;
	
	public MapPanel(int zoom, System system) {
		
		super();
		
		_width = 0;
		_height = 0;
		
		_system = system;
		
		_selectedCell = null;
		
		_selectedColorEntity = null;
		
		_selectedEntityHeight = 0;		
		_selectedEntityWidth = 0;
		
		_mouseX = 0;
		_mouseY = 0;
		
		_colorCellMap = null;
		_colorEntityMap = null;
		
		changeZoom(zoom);

		this.addMouseListener(this);
		this.addMouseWheelListener(this);
		this.addMouseMotionListener(this);
		
	}
	
	protected void paintComponent(Graphics g) {
		
		super.paintComponent(g);
		
		// Establezco el color en el que quiero pintar el fondo.
		g.setColor(Color.WHITE);
		// Dibujo un rectángulo con origen en el 0,0 y cuyo tamaño es todo el panel.
		// Así consigo rellenar todo el panel de color blanco y lo dejo preparado para pintar las celdas del mapa.
		g.fillRect(0, 0, getWidth(), getHeight());
		
		if (_colorCellMap != null)
			// Dibujo todas las casillas del mapa llamando en cada caso a la función que me dibuja una casilla con el grosor especificado.
			// Al mismo tiempo Relleno las casillas del color especificado en el mapa.
			for (int x = 0; x < _width; x++)
				for (int y = 0; y < _height; y++) {
					
					drawGrid(x, y, Color.BLACK, g);
					fillGrid(x, y, _colorCellMap[x][y], g);
					
				}
		
		if (_colorEntityMap != null)
			for (int x = 0; x < _width; x++)
				for (int y = 0; y < _height; y++) {
					
					if (_colorEntityMap[x][y] != null)
						fillEntityGrid(x, y, _colorEntityMap[x][y], g);
					
				}
		
		if (_selectedColorEntity != null)
			drawShadowEntity(_mouseX, _mouseY, _selectedEntityHeight, _selectedEntityWidth, _selectedColorEntity, 0.5F, g);
		
		if (_selectedCell != null)
			selectCell(g);
		
	}
	
	private void drawGrid(int x, int y, Color color, Graphics g) {
		
		g.setColor(color);
		/* Este for dibuja un cuadrado con un borde del número de píxeles especificado.
		 * En realidad lo que hace es dibujar tantos cuadrados sin relleno como número de borde se pase como parámetro.
		 * La función genérica del for está sacada de dibujar borde de tamaño 2 con las dos siguientes instrucciones:
		 * g.drawRect(x * _grid, y * _grid, _grid, _grid);
		 * g.drawRect((x * _grid) + 1, (y * _grid) + 1, _grid - (1 * 2), _grid - (1 * 2));
		 */
		for (int i = 1; i <= _border; i++)
			g.drawRect((x * _grid) + (i - 1), (y * _grid) + (i - 1), _grid - ((i - 1) * 2), _grid - ((i - 1) * 2));
		
	}
	
	private void fillGrid(int x, int y, Color color, Graphics g) {
		
		/* Función de dibujado de una casilla con el color especificado.
		 * Las constantes usadas en la función han sido calculadas para ajustar el cuadrado a la casilla correspondiente.
		 */
		
		g.setColor(color);
		g.fill3DRect((x * _grid) + _border, (y * _grid) + _border, _grid - ((_border * 2) - 1), _grid - ((_border * 2) - 1), true);
		
	}
	
	private void fillEntityGrid(int x, int y, Color color, Graphics g) {
		
		g.setColor(color);
		g.fillOval((x * _grid) + _border, (y * _grid) + _border, _grid - ((_border * 2) - 1), _grid - ((_border * 2) - 1));
		
	}
	
	private void drawShadowEntity(int x, int y, int height, int width, Color color, float alpha, Graphics g) {
		
		Graphics2D g2 = (Graphics2D) g;
		g2.setColor(color);
		g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, alpha));
		g2.fill3DRect((x / _grid) * _grid, (y / _grid) * _grid, width * _grid, height * _grid, true);
	}
	
	private void changeZoom(int zoom) {
		
		// Compruebo que el zoom no se me va a cero o valores negativos porque daría como resultado valores extraños de _grid.
		if (zoom < 1)
			_zoom = 1;
		else
			_zoom = zoom;
		
		/* Actualizo el valor del grid siempre.
		 * Hago esto para que el mapa pueda entrar en pantalla con un valor mínimo de 3 píxeles por celda. La movida está en que mas abajo
		 * llega un momento en que no actualizo el valor del borde, de forma que el grid pueda seguir siendo mas pequeño pero el borde
		 * se quede a un valor mínimo de 1 para que halla borde siempre independientemente del nivel de zoom.
		 */
		_grid = _zoom * 3;
		
		// Si el zoom está dentro del rango correcto actualizo el _border. Sino, se queda en el valor mínimo: 1.
		if (_zoom >= 6)
			_border = _zoom / 6;
		
		// Calculo la nueva dimensión del panel.
		Dimension d = new Dimension(_width * _grid, _height * _grid);
		setPreferredSize(d);
		
		// Repinto.
		this.repaint();
		
	}
	
	private void selectCell(Graphics g) {
		
		drawGrid(_selectedCell.getX(), _selectedCell.getY(), Color.YELLOW, g);
		
	}
	
	private void deSelectCell(Graphics g) {
		
		if (_selectedCell != null) {
			
			drawGrid(_selectedCell.getX(), _selectedCell.getY(), Color.BLACK, g);
			
			_selectedCell = null;
			
		}
		
	}
	
	private Color cellTypeToColor(CellType cellType) {
		
		return _system.getPreferencesColorTypeCell(cellType);
		
	}
	
	private Color entityTypeToColor(EntityType entityType) {
		
		return _system.getPreferencesColorTypeEntity(entityType);
		
	}
	
	private void newEmptyMap(int width, int height) {
		
		_width = width;
		_height = height;
		
		_colorCellMap = new Color[_width][_height];
		_colorEntityMap = new Color[_width][_height];
		
		Dimension d = new Dimension(_width * _grid, _height * _grid);
		setPreferredSize(d);
		
	}
	
	public void newMap(int width, int height, CellType basicCell) {
		
		newEmptyMap(width, height);
		
		Color basicColor = cellTypeToColor(basicCell);
		for (int x = 0; x < _width; x++)
			for (int y = 0; y < _height; y++) {
				
				_colorCellMap[x][y] = basicColor;
				_colorEntityMap[x][y] = null;
				
			}
		
		_system.newMap(_width, _height, basicCell);
		
		repaint();
		
	}
	
	public void repaint() {
		
		super.repaint();
		
		JViewport parent = (JViewport) getParent();
		
		if (parent != null)
			parent.setView(this);
		
	}

	@Override
	public void mouseClicked(MouseEvent e) {

		if (e.getButton() == MouseEvent.BUTTON1) {
			
			int x = e.getX() / _grid;
			int y = e.getY() / _grid;
			
			if ((x < _width) && (y < _height))
			// If complejo pero necesario para calcular que el click del ratón no caiga en un borde.
				if ((e.getX() > ((x * _grid) + (_border - 1))) && (e.getX() < ((x * _grid) + (_grid - (_border - 1)))) && 
					(e.getY() > ((y * _grid) + (_border - 1))) && (e.getY() < ((y * _grid) + (_grid - (_border - 1))))) {
					_system.clicked(new Position(x, y));
				}
		
		}
		else
			if (e.getButton() == MouseEvent.BUTTON3) {
				
				_system.clickedSecond();
				
			}
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		
		int tmpZoom = _zoom;
		
		if (e.getWheelRotation() < 0)
			tmpZoom++;
		else
			tmpZoom--;
		
		changeZoom(tmpZoom);
		
	}

	@Override
	public void cellSelected(Position cell) {
		
		_selectedCell = cell;
		
		selectCell(getGraphics());
		
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
	public void cellChanged(Position cell, CellType cellType) {
		
		_colorCellMap[cell.getX()][cell.getY()] = cellTypeToColor(cellType);
		
		repaint();
		
	}

	@Override
	public void newMap(int width, int height) {
		
		newEmptyMap(width, height);
		
	}

	@Override
	public void cellDeSelected() {
		
		deSelectCell(getGraphics());
		
		getParent().repaint();
		repaint();
		
	}

	@Override
	public void preferencesChanged() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void typeElementSelected(ElementType elementType, int height, int width) {
		
		if (height != 0) {
			
			_selectedColorEntity = _system.getPreferencesColorTypeEntity((EntityType) elementType);
			
			_selectedEntityHeight = height;
			
			_selectedEntityWidth = width;
			
		}
		
	}

	@Override
	public void typeElementDeSelected() {
		
		_selectedColorEntity = null;
		
		_selectedEntityHeight = 0;
		
		_selectedEntityWidth = 0;
		
	}
	
	@Override
	public void newEntity(Position[] posList, EntityType entityType) {
		
		for (int i = 0; i < posList.length; i++)
			_colorEntityMap[posList[i].getX()][posList[i].getY()] = entityTypeToColor(entityType);
		
		repaint();
		
	}
	
	@Override
	public void removeEntity(Position[] posList) {
		
		for (int i = 0; i < posList.length; i++)
			_colorEntityMap[posList[i].getX()][posList[i].getY()] = null;
		
		repaint();
		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		
		if (_selectedColorEntity != null) {
			
			if ((e.getX() / _grid) > (_width - _selectedEntityWidth))
				_mouseX = (_width * _grid) - (_selectedEntityWidth * _grid);
			else
				_mouseX = e.getX();
			
			if ((e.getY() / _grid) > (_height - _selectedEntityHeight))
				_mouseY = (_height * _grid) - (_selectedEntityHeight * _grid);
			else
				_mouseY = e.getY();
			
			repaint();
			
		}
		
	}

}
