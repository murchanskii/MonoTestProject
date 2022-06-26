using System;

public class MyNode : Node
{
    public override void Start()
    {
        Print("MyNode.Start() from C#");
    }

    public override void Update()
    {
        Print("MyNode.Update() from C#");
    }

    public override void PrintPosition()
    {
        base.PrintPosition();
    }

    public override void SetPosition(float x, float y, float z)
    {
        base.SetPosition(x, y, z);
    }

    private void Print(string str)
    {
        Console.WriteLine(str);
    }
}