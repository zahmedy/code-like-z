type Logger interface {
	Log(message string)
}

type ConsoleLogger strcut{}

func (c *ConsoleLogger) Log(message string) {
	fmt.Println(message)
}