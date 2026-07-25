// ============================================================
// app.js — منطق الشات بوت الصوتي (يعمل في المتصفح)
// ============================================================

const micBtn = document.getElementById("micBtn");
const micIcon = document.getElementById("micIcon");
const chatLog = document.getElementById("chatLog");
const statusText = document.getElementById("statusText");

// عنوان الخادم الخلفي الذي يستدعي Gemini بأمان (انظر process.php)
// مسار نسبي حتى يعمل تلقائيًا مهما كان اسم النطاق على InfinityFree
const BACKEND_URL = "process.php";

// اللغة المستخدمة للتعرف على الصوت وللنطق
const LANG = "ar-SA";

let isListening = false;

// --------------------------------------------------------
// 1) إعداد التعرف على الصوت (Speech-to-Text)
// --------------------------------------------------------
const SpeechRecognitionAPI = window.SpeechRecognition || window.webkitSpeechRecognition;

if (!SpeechRecognitionAPI) {
  statusText.textContent = "متصفحك لا يدعم التعرف على الصوت. جرّب Chrome أو Edge.";
  micBtn.disabled = true;
} else {
  const recognition = new SpeechRecognitionAPI();
  recognition.lang = LANG;
  recognition.interimResults = false;
  recognition.maxAlternatives = 1;

  micBtn.addEventListener("click", () => {
    if (isListening) {
      recognition.stop();
      return;
    }
    try {
      recognition.start();
    } catch (err) {
      console.error(err);
      addMessage("bot", `حدث خطأ: ${err.message}`);
    }
  });

  recognition.onstart = () => {
    isListening = true;
    micBtn.classList.add("listening");
    micIcon.textContent = "⏹️";
    statusText.textContent = "أستمع الآن... تحدّث بحرية";
  };

  recognition.onend = () => {
    isListening = false;
    micBtn.classList.remove("listening");
    micIcon.textContent = "🎤";
    statusText.textContent = "اضغط على الميكروفون وابدأ الحديث";
  };

  recognition.onerror = (event) => {
    console.error("خطأ في التعرف على الصوت:", event.error);
    statusText.textContent = "لم أستطع سماعك، حاول مرة أخرى";
  };

  recognition.onresult = async (event) => {
    const userText = event.results[0][0].transcript;
    if (!userText) return;

    addMessage("user", userText);
    const thinkingEl = addMessage("bot", "...يفكر", { thinking: true });

    try {
      const reply = await askGemini(userText);
      thinkingEl.remove();
      addMessage("bot", reply);
      speak(reply);
    } catch (err) {
      console.error(err);
      thinkingEl.remove();
      addMessage("bot", "حدث خطأ أثناء الاتصال بالخادم. حاول مجددًا.");
    }
  };
}

// --------------------------------------------------------
// 2) الاتصال بالخادم الخلفي الذي يستدعي Gemini
//    (لا نستدعي Gemini مباشرة من المتصفح لحماية مفتاح الـ API)
// --------------------------------------------------------
async function askGemini(prompt) {
  const res = await fetch(BACKEND_URL, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ prompt }),
  });

  const data = await res.json();

  if (!res.ok) {
    throw new Error(data.error || `فشل الطلب: ${res.status}`);
  }

  return data.reply || "لم يصل رد من الخادم.";
}

// --------------------------------------------------------
// 3) تحويل النص إلى كلام (Text-to-Speech)
// --------------------------------------------------------
function speak(text) {
  if (!("speechSynthesis" in window)) return;

  window.speechSynthesis.cancel(); // إيقاف أي نطق سابق
  // ننطق نص "نظيف" بدون رموز Markdown حتى لا يقرأها الصوت حرفيًا
  const cleanText = stripMarkdown(text);
  const utterance = new SpeechSynthesisUtterance(cleanText);
  utterance.lang = LANG;
  utterance.rate = 1;
  window.speechSynthesis.speak(utterance);
}

// --------------------------------------------------------
// 4) تحويل Markdown البسيط (من Gemini) إلى HTML آمن
// --------------------------------------------------------
function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

function formatBotText(rawText) {
  let text = escapeHtml(rawText);

  // عناوين ### أو ## أو #
  text = text.replace(/^### (.*)$/gm, "<h4>$1</h4>");
  text = text.replace(/^## (.*)$/gm, "<h3>$1</h3>");
  text = text.replace(/^# (.*)$/gm, "<h2>$1</h2>");

  // خط عريض **نص**
  text = text.replace(/\*\*(.*?)\*\*/g, "<strong>$1</strong>");

  // عناصر قائمة تبدأ بـ * أو -
  text = text.replace(/^[*-] (.*)$/gm, "• $1");

  // خطوط فاصلة --- أو ***
  text = text.replace(/^(---|\*\*\*)$/gm, "");

  // الأسطر الجديدة إلى <br>
  text = text.replace(/\n/g, "<br>");

  return text;
}

// نسخة نظيفة من النص بدون أي رموز Markdown (تُستخدم للنطق الصوتي)
function stripMarkdown(rawText) {
  return rawText
    .replace(/^#{1,6}\s?/gm, "")
    .replace(/\*\*(.*?)\*\*/g, "$1")
    .replace(/^[*-]\s?/gm, "")
    .replace(/^(---|\*\*\*)$/gm, "")
    .trim();
}

// --------------------------------------------------------
// أدوات مساعدة لواجهة الدردشة
// --------------------------------------------------------
function addMessage(role, text, opts = {}) {
  const el = document.createElement("div");
  el.className = `message ${role}${opts.thinking ? " thinking" : ""}`;
  const p = document.createElement("p");

  if (role === "bot" && !opts.thinking) {
    // نسمح بتنسيق HTML بسيط وآمن لردود البوت فقط
    p.innerHTML = formatBotText(text);
  } else {
    p.textContent = text;
  }

  el.appendChild(p);
  chatLog.appendChild(el);
  chatLog.scrollTop = chatLog.scrollHeight;
  return el;
}