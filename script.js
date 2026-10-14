let currentLang = 'es';
let drawerOpen = false;

const responses = {
    si: { es: '¡Genial! Gracias por tu opinión 😊', en: 'Great! Thanks for your feedback 😊' },
    no: { es: 'Gracias, vamos a mejorar 💪', en: 'Thanks, we will improve 💪' }
};

function toggleDrawer() {
    drawerOpen ? closeDrawer() : openDrawer();
}

function openDrawer() {
    drawerOpen = true;
    document.getElementById('navDrawer').classList.add('open');
    document.getElementById('backdrop').classList.add('open');
    document.getElementById('hamburger').classList.add('open');
    document.body.style.overflow = '';
}

function closeDrawer() {
    drawerOpen = false;
    document.getElementById('navDrawer').classList.remove('open');
    document.getElementById('backdrop').classList.remove('open');
    document.getElementById('hamburger').classList.remove('open');
    document.getElementById('langMenu').classList.remove('open');
    document.getElementById('langSelector').classList.remove('open');
}

function setLang(lang) {
    currentLang = lang;
    document.getElementById('currentLangLabel').textContent = lang === 'es' ? 'ESPAÑOL' : 'ENGLISH';
    document.getElementById('langMenu').classList.remove('open');
    document.getElementById('langSelector').classList.remove('open');
    document.querySelectorAll('[data-es][data-en]').forEach(el => {
        el.textContent = el.getAttribute('data-' + lang);
    });
    document.documentElement.lang = lang;
    document.getElementById('fb-response').textContent = '';
    document.querySelectorAll('.fb-btn').forEach(b => b.classList.remove('selected'));
}

function responder(opcion) {
    document.querySelectorAll('.fb-btn').forEach(b => b.classList.remove('selected'));
    document.getElementById('btn-' + opcion).classList.add('selected');
    document.getElementById('fb-response').textContent = responses[opcion][currentLang];
}

function toggleLangMenu() {
    const sel = document.getElementById('langSelector');
    const menu = document.getElementById('langMenu');
    sel.classList.toggle('open');
    menu.classList.toggle('open');
}

// Cerrar con ESC
document.addEventListener('keydown', e => {
    if (e.key === 'Escape' && drawerOpen) closeDrawer();
});

// Scroll reveal
const observer = new IntersectionObserver(entries => {
    entries.forEach((entry, i) => {
        if (entry.isIntersecting) {
            setTimeout(() => entry.target.classList.add('visible'), i * 60);
            observer.unobserve(entry.target);
        }
    });
}, { threshold: 0.08 });

document.querySelectorAll('.reveal').forEach(el => observer.observe(el));