using System;
using System.Runtime.InteropServices;
using System.Text;

public class Node
{
    private IntPtr _nodeInstance;

    public Node()
    {
        _nodeInstance = CreateNode();
    }

    ~Node()
    {
        ReleaseNode(_nodeInstance);
    }

    virtual public void Start()
    {
        DoStart(_nodeInstance);
    }

    virtual public void Update()
    {
        DoUpdate(_nodeInstance);
    }

    virtual public void PrintPosition()
    {
        Console.WriteLine(GetPositionX() + ", " +
            GetPositionY() + ", " +
            GetPositionZ());
    }

    virtual public void SetPosition(float x, float y, float z)
    {
        SetPosition(_nodeInstance, x, y, z);
    }

    public float GetPositionX()
    {
        return GetPositionX(_nodeInstance);
    }

    public float GetPositionY()
    {
        return GetPositionY(_nodeInstance);
    }

    public float GetPositionZ()
    {
        return GetPositionZ(_nodeInstance);
    }

    public void PrintName()
    {
        Console.WriteLine(GetName());
    }

    public void SetName(string name)
    {
        byte[] nameBytes = Encoding.Default.GetBytes(name);
        var nameStr = Encoding.UTF8.GetString(nameBytes);

        nameStr = nameStr + char.MinValue;
        byte[] pInBuffer = Encoding.UTF8.GetBytes(nameStr);
        IntPtr inputBuffer = Marshal.AllocHGlobal(pInBuffer.Length * sizeof(byte));
        Marshal.Copy(pInBuffer, 0, inputBuffer, pInBuffer.Length);
        SetName(_nodeInstance, inputBuffer);
        Marshal.FreeHGlobal(inputBuffer);
    }

    public string GetName()
    {
        var maxSize = int.MaxValue;
        byte[] resultStrBytes = new byte[maxSize];
        var length = GetName(_nodeInstance, resultStrBytes);
        var resultStr = System.Text.Encoding.UTF8.GetString(resultStrBytes);
        resultStr = resultStr.Substring(0, (int)length);
        return resultStr;
    }

    #region DllDescription

    [DllImport("__Internal", EntryPoint = "CreateNode")]
    private static extern IntPtr CreateNode();
    [DllImport("__Internal", EntryPoint = "ReleaseNode")]
    private static extern void ReleaseNode(IntPtr ptr);
    [DllImport("__Internal", EntryPoint = "NodeDoStart")]
    private static extern void DoStart(IntPtr ptr);
    [DllImport("__Internal", EntryPoint = "NodeDoUpdate")]
    private static extern void DoUpdate(IntPtr ptr);
    [DllImport("__Internal", EntryPoint = "NodeSetPosition")]
    private static extern void SetPosition(IntPtr ptr, float posX, float posY, float posZ);
    [DllImport("__Internal", EntryPoint = "NodeGetPositionX")]
    private static extern float GetPositionX(IntPtr ptr);
    [DllImport("__Internal", EntryPoint = "NodeGetPositionY")]
    private static extern float GetPositionY(IntPtr ptr);
    [DllImport("__Internal", EntryPoint = "NodeGetPositionZ")]
    private static extern float GetPositionZ(IntPtr ptr);
    [DllImport("__Internal", EntryPoint = "NodeSetName")]
    private static extern void SetName(IntPtr ptr, IntPtr name);
    [DllImport("__Internal", EntryPoint = "NodeGetName")]
    private static extern int GetName(IntPtr ptr, byte[] name);

    #endregion
}