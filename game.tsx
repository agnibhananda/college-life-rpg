import { NextResponse } from 'next/server'

type Character = {
  name: string
  health: number
  maxHealth: number
  energy: number
  maxEnergy: number
  exam_prep: number
  charisma: number
  stress: number
  intelligence: number
  experience: number
  level: number
  semester: number
  cgpa: number
  credits: number
  money: number
  dance_skill: number
}

type Quest = {
  name: string
  description: string
  completed: boolean
  experienceReward: number
  moneyReward: number
  cgpaBoost: number
}

type Club = {
  name: string
  description: string
  memberCount: number
  joined: boolean
}

type Location = {
  name: string
  description: string
  unlocked: boolean
  stress_modifier: number
  study_bonus: number
}

type Story = {
  act: number
  corruption_exposed: boolean
  library_secured: boolean
  dance_battle_won: boolean
  deanDefeated: boolean
}

type GameState = {
  player: Character
  quests: Quest[]
  clubs: Club[]
  locations: Location[]
  story: Story
  currentDay: number
  currentMonth: number
}

let gameState: GameState = {
  player: {
    name: '',
    health: 100,
    maxHealth: 100,
    energy: 100,
    maxEnergy: 100,
    exam_prep: 0,
    charisma: 10,
    stress: 0,
    intelligence: 10,
    experience: 0,
    level: 1,
    semester: 1,
    cgpa: 0,
    credits: 0,
    money: 1000,
    dance_skill: 0
  },
  quests: [],
  clubs: [
    { name: "Open Source Development Society", description: "A club for Development enthusiasts and aspiring programmers.", memberCount: 30, joined: false },
    { name: "Knuth Programming hub", description: "Improve your DSA and Competitive programming skills", memberCount: 50, joined: false },
    { name: "DebSoc", description: "Improve your public speaking and argumentation skills.", memberCount: 25, joined: false },
    { name: "Cresendo", description: "Improve your singing and music skills", memberCount: 20, joined: false },
    { name: "Thespian", description: "Express yourself through acting and stage production.", memberCount: 20, joined: false }
  ],
  locations: [
    { name: "Main Academic Block", description: "The heart of academic life where Professor Pataka roams. Watch out for surprise quizzes!", unlocked: true, stress_modifier: 10, study_bonus: 20 },
    { name: "Chintu's Canteen", description: "The legendary hangout spot. Best maggi in town and source of valuable information!", unlocked: true, stress_modifier: -10, study_bonus: -5 },
    { name: "Library", description: "A battleground during exams. Prime study spots are highly contested!", unlocked: true, stress_modifier: 5, study_bonus: 30 },
    { name: "Hostel", description: "Your safe haven... usually. Watch out for Risky and Misky!", unlocked: true, stress_modifier: -15, study_bonus: 10 },
    { name: "College Ground", description: "Where dance battles and cultural events happen. Perfect for socializing!", unlocked: true, stress_modifier: -20, study_bonus: -10 },
    { name: "Computer Lab", description: "Home of coding battles and technical events. Tamboli's favorite spot.", unlocked: true, stress_modifier: 15, study_bonus: 25 },
    { name: "Dean's Office", description: "The final boss arena. Currently locked - need to progress story to access.", unlocked: false, stress_modifier: 30, study_bonus: 0 }
  ],
  story: {
    act: 1,
    corruption_exposed: false,
    library_secured: false,
    dance_battle_won: false,
    deanDefeated: false
  },
  currentDay: 1,
  currentMonth: 1
}

function processCommand(input: string): string[] {
  const output: string[] = []

  if (!gameState.player.name) {
    gameState.player.name = input
    output.push(`Welcome, ${input}!`, 'Type "help" for a list of commands.', 'What would you like to do?')
    return output
  }

  switch (input.toLowerCase()) {
    case 'help':
      output.push(
        'Available commands:',
        'status - Check your current status',
        'study - Study to increase intelligence',
        'socialize - Socialize to increase charisma',
        'sleep - Sleep to restore energy',
        'eat - Eat to restore health',
        'change location - Move to a different area',
        'join club - Join a club',
        'quit - Exit the game'
      )
      break

    case 'status':
      output.push(
        `Name: ${gameState.player.name}`,
        `Health: ${gameState.player.health}/${gameState.player.maxHealth}`,
        `Energy: ${gameState.player.energy}/${gameState.player.maxEnergy}`,
        `Intelligence: ${gameState.player.intelligence}`,
        `Charisma: ${gameState.player.charisma}`,
        `Stress: ${gameState.player.stress}`,
        `Experience: ${gameState.player.experience}`,
        `Level: ${gameState.player.level}`,
        `Semester: ${gameState.player.semester}`,
        `CGPA: ${gameState.player.cgpa.toFixed(2)}`,
        `Credits: ${gameState.player.credits}`,
        `Money: ₹${gameState.player.money}`,
        `Exam preparation: ${gameState.player.exam_prep}`,
        `Dance skill: ${gameState.player.dance_skill}`,
        `Current day: ${gameState.currentDay}`,
        `Current month: ${gameState.currentMonth}`,
        `Current act: ${gameState.story.act}`
      )
      break

    case 'study':
      if (gameState.player.energy >= 10) {
        gameState.player.intelligence += 1
        gameState.player.energy -= 10
        gameState.player.exam_prep += 5
        gameState.player.stress = Math.min(gameState.player.stress + 5, 100)
        output.push('You studied hard. Intelligence and exam preparation increased!')
      } else {
        output.push("You're too tired to study. Get some sleep!")
      }
      break

    case 'socialize':
      if (gameState.player.energy >= 5) {
        gameState.player.charisma += 1
        gameState.player.energy -= 5
        gameState.player.stress = Math.max(gameState.player.stress - 5, 0)
        output.push('You socialized with friends. Charisma increased and stress decreased!')

        if (gameState.story.act === 2 && !gameState.story.dance_battle_won && gameState.player.charisma >= 20) {
          output.push('Misky notices your growing popularity...')
          output.push('She challenges you to a dance battle!')
          if (Math.random() < 0.6) {
            gameState.story.dance_battle_won = true
            gameState.player.dance_skill += 10
            output.push("You've won the dance battle! You're now the dance champion!")
          } else {
            output.push("You lost the dance battle. Keep practicing!")
          }
        }
      } else {
        output.push("You're too tired to socialize. Get some sleep!")
      }
      break

    case 'sleep':
      gameState.player.energy = Math.min(gameState.player.energy + 50, gameState.player.maxEnergy)
      gameState.player.health = Math.min(gameState.player.health + 10, gameState.player.maxHealth)
      gameState.player.stress = Math.max(gameState.player.stress - 10, 0)
      gameState.currentDay++
      if (gameState.currentDay > 30) {
        gameState.currentDay = 1
        gameState.currentMonth++
        if (gameState.currentMonth > 12) {
          gameState.currentMonth = 1
          gameState.player.semester++
        }
      }
      output.push('You slept well. Energy restored and stress decreased!')
      output.push(`It's now day ${gameState.currentDay} of month ${gameState.currentMonth}, semester ${gameState.player.semester}.`)
      break

    case 'eat':
      output.push('Where would you like to eat?')
      output.push('1. Cafeteria (₹30)')
      output.push('2. Local Restaurant (₹150)')
      output.push('3. Mess (₹0)')
      output.push('Enter the number of your choice:')
      break

    case '1':
    case '2':
    case '3':
      const choice = parseInt(input)
      switch (choice) {
        case 1:
          if (gameState.player.money >= 30) {
            gameState.player.money -= 30
            gameState.player.health += 15
            gameState.player.energy += 20
            output.push('You eat a meal at the cafeteria.')
          } else {
            output.push("You don't have enough money to eat at the cafeteria.")
          }
          break
        case 2:
          if (gameState.player.money >= 150) {
            gameState.player.money -= 150
            gameState.player.health += 25
            gameState.player.energy += 30
            gameState.player.stress -= 10
            output.push('You enjoy a delicious meal at a local restaurant.')
          } else {
            output.push("You don't have enough money to eat at a restaurant.")
          }
          break
        case 3:
          gameState.player.health += 10
          gameState.player.energy += 15
          output.push('You eat from the campus mess, Annapurna.')
          break
      }
      gameState.player.health = Math.min(gameState.player.health, gameState.player.maxHealth)
      gameState.player.energy = Math.min(gameState.player.energy, gameState.player.maxEnergy)
      gameState.player.stress = Math.max(gameState.player.stress, 0)
      break

    case 'change location':
      output.push('Available Locations:')
      gameState.locations.forEach((location, index) => {
        if (location.unlocked) {
          output.push(`${index + 1}. ${location.name}`)
          output.push(`   ${location.description}`)
          output.push(`   Study Bonus: ${location.study_bonus > 0 ? '+' : ''}${location.study_bonus}`)
          output.push(`   Stress Impact: ${location.stress_modifier > 0 ? '+' : ''}${location.stress_modifier}`)
          output.push('')
        }
      })
      output.push('Enter the number of the location you want to go to:')
      break

    case 'join club':
      output.push('Available Clubs:')
      gameState.clubs.forEach((club, index) => {
        output.push(`${index + 1}. ${club.name} (${club.memberCount} members)`)
        output.push(`   Description: ${club.description}`)
      })
      output.push('Enter the number of the club you want to join:')
      break

    default:
      if (input.startsWith('location ')) {
        const locationIndex = parseInt(input.split(' ')[1]) - 1
        if (locationIndex >= 0 && locationIndex < gameState.locations.length && gameState.locations[locationIndex].unlocked) {
          const location = gameState.locations[locationIndex]
          gameState.player.stress += location.stress_modifier
          output.push(`You've moved to ${location.name}`)
          output.push(`Stress ${location.stress_modifier > 0 ? 'increased' : 'decreased'} by ${Math.abs(location.stress_modifier)}`)
          if (location.study_bonus !== 0) {
            output.push(`Study effectiveness ${location.study_bonus > 0 ? 'increased' : 'decreased'} by ${Math.abs(location.study_bonus)}%`)
          }
        } else {
          output.push('Invalid location choice!')
        }
      } else if (input.startsWith('club ')) {
        const clubIndex = parseInt(input.split(' ')[1]) - 1
        if (clubIndex >= 0 && clubIndex < gameState.clubs.length) {
          const club = gameState.clubs[clubIndex]
          if (!club.joined) {
            club.joined = true
            club.memberCount++
            output.push(`You've joined the ${club.name}!`)
            gameState.player.experience += 20
            gameState.player.charisma += 2
            gameState.player.stress += 5
          } else {
            output.push("You're already a member of this club.")
          }
        } else {
          output.push('Invalid club choice!')
        }
      } else {
        output.push('Unknown command. Type "help" for a list of commands.')
      }
  }

  // Check for act progression
  const previousAct = gameState.story.act
  switch (gameState.story.act) {
    case 1:
      if (gameState.player.charisma >= 15 && gameState.player.intelligence >= 15) {
        gameState.story.act = 2
        output.push('=== Congratulations! You\'ve advanced to Act 2! ===')
        output.push('You\'ve gained enough confidence to enter the social scene!')
      }
      break
    case 2:
      if (gameState.story.dance_battle_won) {
        gameState.story.act = 3
        output.push('=== Congratulations! You\'ve advanced to Act 3! ===')
        output.push('Your social achievements have earned you respect. Time to focus on academics!')
      }
      break
    case 3:
      if (gameState.story.library_secured && gameState.player.exam_prep >= 50) {
        gameState.story.act = 4
        output.push('=== Congratulations! You\'ve advanced to Act 4! ===')
        output.push('While studying, you\'ve discovered hints of corruption...')
      }
      break
  }

  if (previousAct !== gameState.story.act) {
    output.push('Press Enter to continue...')
  }

  return output
}

export async function POST(req: Request) {
  const { input } = await req.json()
  const output = processCommand(input)
  return NextResponse.json({ output: output.join('\n') })
}
