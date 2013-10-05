using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;

namespace SeparationOfConcerns
{
  public partial class MainWindow : Window
  {
    public MainWindow()
    {
      InitializeComponent();
      Init();
    }

    public void Init()
    {
      var cardStyle = App.Current.Resources["Card"] as Style;
      var flippedStyle = App.Current.Resources["Flipped"] as Style;

      var children = VisualTreeHelper.GetChildrenCount(exampleGrid);

      for (var i = 0; i < children; i++)
      {
        var child = VisualTreeHelper.GetChild(exampleGrid, i) as Rectangle;

        if (child != null && cardStyle != null && child.Style == cardStyle)
        {
          child.MouseLeave += (o, args) => child.Style = cardStyle;
          child.MouseEnter += (o, args) => child.Style = flippedStyle;
        }
      }

    }
  }
}
