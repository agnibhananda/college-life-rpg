'use client'

import { useState, useEffect, useRef } from 'react'
import { Terminal } from 'lucide-react'

export default function Component() {
  const [input, setInput] = useState('')
  const [output, setOutput] = useState<string[]>(['Welcome to College Life RPG!', 'Enter your name to begin:'])
  const inputRef = useRef<HTMLInputElement>(null)
  const outputRef = useRef<HTMLDivElement>(null)

  useEffect(() => {
    if (outputRef.current) {
      outputRef.current.scrollTop = outputRef.current.scrollHeight
    }
    if (inputRef.current) {
      inputRef.current.focus()
    }
  }, [output])

  const handleInput = async (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === 'Enter') {
      setOutput((prev) => [...prev, `> ${input}`])
      try {
        const response = await fetch('/api/game', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ input }),
        })
        const data = await response.json()
        setOutput((prev) => [...prev, ...data.output.split('\n')])
      } catch (error) {
        console.error('Error communicating with the game server:', error)
        setOutput((prev) => [...prev, 'Error: Unable to communicate with the game server.'])
      }
      setInput('')
    }
  }

  return (
    <div className="flex items-center justify-center min-h-screen bg-gray-100 p-4">
      <div className="w-full max-w-4xl bg-black text-green-400 p-4 rounded-lg shadow-lg font-mono">
        <div className="flex items-center mb-4">
          <Terminal className="mr-2" />
          <h1 className="text-xl font-bold">College Life RPG Terminal</h1>
        </div>
        <div ref={outputRef} className="h-96 overflow-y-auto mb-4 whitespace-pre-wrap">
          {output.map((line, index) => (
            <div key={index}>{line}</div>
          ))}
        </div>
        <div className="flex items-center">
          <span className="mr-2">{'>'}</span>
          <input
            ref={inputRef}
            type="text"
            value={input}
            onChange={(e) => setInput(e.target.value)}
            onKeyDown={handleInput}
            className="flex-grow bg-transparent outline-none"
            aria-label="Command input"
          />
        </div>
      </div>
    </div>
  )
}
